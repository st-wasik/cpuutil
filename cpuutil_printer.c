#include "cpuutil_printer.h"

#include <assert.h>
#include <memory.h>
#include <stdlib.h>

struct cpuutil_printer
{
    const parameters_t* parameters;
};

cpuutil_printer_t* cpuutil_printer_create(const parameters_t* parameters)
{
    cpuutil_printer_t* cpuutil_printer = malloc(sizeof(struct cpuutil_printer));
    assert(cpuutil_printer);

    memset(cpuutil_printer, 0, sizeof(struct cpuutil_printer));

    cpuutil_printer->parameters = parameters;

    return cpuutil_printer;
}

void cpuutil_printer_destroy(cpuutil_printer_t* cpuutil_printer)
{
    assert(cpuutil_printer);

    free(cpuutil_printer);
}

void cpuutil_printer_print(cpuutil_printer_t* cpuutil_printer, const cpuutil_state_t* cpuutil_state)
{
    assert(cpuutil_printer);
    assert(cpuutil_state);

    if(cpuutil_state->step_number == 0)
    {
        if(cpuutil_printer->parameters->print_current_utilization)
            printf("   ALL");

        if(cpuutil_printer->parameters->print_average_utilization)
            printf("   ALL");

        printf("  ");

        for(int i = 0; i < cpuutil_state->items_count - 1; i++)
        {
            if(cpuutil_printer->parameters->print_current_utilization)
                printf(" CPU%02d", i);

            if(cpuutil_printer->parameters->print_average_utilization)
                printf(" CPU%02d", i);

            printf("  ");
        }

        printf("\n");

        for(int i = 0; i < cpuutil_state->items_count; i++)
        {
            if(cpuutil_printer->parameters->print_current_utilization)
                printf("  CURR");

            if(cpuutil_printer->parameters->print_average_utilization)
                printf("   AVG");

            printf("  ");
        }

        printf("       STEP       TIME");
    }
    else
    {
        for(int i = 0; i < cpuutil_state->items_count; i++)
        {
            if(cpuutil_printer->parameters->print_current_utilization)
                printf(" %5.1f", cpuutil_state->last_utilizations[i] * 100);

            if(cpuutil_printer->parameters->print_average_utilization)
                printf(" %5.1f", cpuutil_state->averages[i].value * 100.0);

            printf("  ");
        }

        if(cpuutil_state->is_utilization_invalid)
            fprintf(stderr, "WARN: reading too fast! Some counters haven't been updated since the last read. Increase the read interval.\n");

        printf("     %6lu     %6.2f", cpuutil_state->step_number, 0.000001 * cpuutil_state->execution_time_usec);
    }

    printf("\n");
    fflush(stdout);
}