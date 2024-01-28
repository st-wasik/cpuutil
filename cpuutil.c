#include "cpuutil.h"

#include <unistd.h>
#include <sys/time.h>
#include <sys/param.h>
#include <assert.h>
#include <memory.h>

#include "cpustat_reader.h"
#include "average.h"
#include "elapsed_timer.h"
#include "cpuutil_state.h"
#include "cpuutil_printer.h"

int cpuutil_run(const parameters_t* parameters)
{
    int return_code = 0;

    cpustat_reader_t* reader = cpustat_reader_create();
    cpuutil_printer_t* printer = cpuutil_printer_create(parameters);

    size_t cpustats_count = 0;
    cpustat_t* current_read = NULL;
    cpustat_t* last_read = NULL;
    cpuutil_state_t* state = NULL;

    long long expected_time_after_step = 0;
    elapsed_timer_t* execution_timer = elapsed_timer_create();

    for(size_t read_number = 0; 1; read_number++)
    {
        if(cpustat_reader_read_cpustats(reader, &current_read, &cpustats_count) != 0)
        {
            return_code = 1;
            break;
        }

        // first read returns average cpu utlization since system start, so skip it
        if(read_number == 0)
        {
            last_read = calloc(cpustats_count, sizeof(cpustat_t));
            assert(last_read);

            state = cpuutil_state_create(cpustats_count);
        }
        else
        {
            state->is_utilization_invalid = 0;

            for(int i = 0; i < cpustats_count; i++)
            {
                cpustat_t stat;

                cpustat_subtract(&stat, current_read + i, last_read + i);
                double utilization = cpustat_calculate_utilization(&stat);
                if(utilization < 0.0)
                {
                    state->is_utilization_invalid = 1;
                    utilization = state->last_utilizations[i];
                }

                state->last_utilizations[i] = utilization;
                average_add(state->averages + i, state->last_utilizations[i]);
            }
        }

        state->step_number = read_number;
        state->execution_time_usec = elapsed_timer_get_elapsed_usec(execution_timer);
        cpuutil_printer_print(printer, state);

        memcpy(last_read, current_read, sizeof(cpustat_t) * cpustats_count);

        expected_time_after_step += parameters->sleep_interval_usec;
        usleep(MAX(0, expected_time_after_step - elapsed_timer_get_elapsed_usec(execution_timer)));
    }

    free(last_read);
    free(current_read);

    cpuutil_state_destroy(state);
    cpustat_reader_destroy(reader);
    cpuutil_printer_destroy(printer);
    elapsed_timer_destroy(execution_timer);

    return return_code;
}