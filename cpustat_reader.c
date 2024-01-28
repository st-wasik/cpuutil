#include "cpustat_reader.h"

#include <assert.h>
#include <stdio.h>
#include <sys/param.h>
#include <string.h>
#include <stdlib.h>

struct cpustat_reader
{
    FILE* file;
    size_t number_of_cpus;
};

cpustat_reader_t* cpustat_reader_create(void)
{
    cpustat_reader_t* cpustat_reader = malloc(sizeof(struct cpustat_reader));
    assert(cpustat_reader);

    memset(cpustat_reader, 0, sizeof(struct cpustat_reader));

    return cpustat_reader;
}

static int cpustat_reader_close_file(cpustat_reader_t* cpustat_reader);

void cpustat_reader_destroy(cpustat_reader_t* cpustat_reader)
{
    assert(cpustat_reader);

    cpustat_reader_close_file(cpustat_reader);
}

static int cpustat_reader_close_file(cpustat_reader_t* cpustat_reader)
{
    assert(cpustat_reader);

    if(cpustat_reader->file == NULL)
        return 0;

    if(fclose(cpustat_reader->file) == EOF)
        return 1;

    cpustat_reader->file = NULL;

    return 0;
}

static int cpustat_reader_open_file(cpustat_reader_t* cpustat_reader)
{
    assert(cpustat_reader);

    if(cpustat_reader->file != NULL && cpustat_reader_close_file(cpustat_reader) != 0)
        return 1;

    cpustat_reader->file = fopen("/proc/stat", "r");

    if(cpustat_reader->file == NULL)
        return 1;

    return 0;
}

static int cpustat_reader_read_cpustat_from_file(cpustat_reader_t* cpustat_reader, cpustat_t* cpustat)
{
    assert(cpustat_reader);
    assert(cpustat_reader->file);
    assert(cpustat);

    return fscanf(cpustat_reader->file, "%8s %llu %llu %llu %llu %llu %llu %llu %llu %llu %llu",
        cpustat->name,
        &cpustat->user,
        &cpustat->nice,
        &cpustat->system,
        &cpustat->idle,
        &cpustat->iowait,
        &cpustat->irq,
        &cpustat->softirq,
        &cpustat->steal,
        &cpustat->guest,
        &cpustat->guest_nice
    );
}

static int cpustat_reader_read_number_of_cpu_lines(cpustat_reader_t* cpustat_reader)
{
    assert(cpustat_reader);

    if(cpustat_reader_open_file(cpustat_reader) != 0)
        return -1;

    size_t length = 0;
    char* line = NULL;
    int read = 0;

    cpustat_reader->number_of_cpus = 0;

    while((read = getline(&line, &length, cpustat_reader->file)) != -1)
    {
        if(strncmp(line, "cpu", MIN(3, read)) != 0)
            break;

        cpustat_reader->number_of_cpus++;
    }

    free(line);

    if(cpustat_reader_close_file(cpustat_reader) != 0)
        return -1;

    return 0;
}

static void cpustat_reader_prepare_buffers(cpustat_reader_t* cpustat_reader, cpustat_t** cpustats_buffer, size_t* cpustats_count)
{
    assert(cpustat_reader);
    assert(cpustats_buffer);
    assert(cpustats_count);
    assert(cpustat_reader->number_of_cpus > 0);

    if(*cpustats_count < cpustat_reader->number_of_cpus)
    {
        free(*cpustats_buffer);
        *cpustats_buffer = NULL;
    }

    if(*cpustats_buffer == NULL)
    {
        *cpustats_buffer = calloc(cpustat_reader->number_of_cpus, sizeof(cpustat_t));
        assert(*cpustats_buffer);
        *cpustats_count = cpustat_reader->number_of_cpus;
    }
}

int cpustat_reader_read_cpustats(cpustat_reader_t* cpustat_reader, cpustat_t** cpustats_buffer, size_t* cpustats_count)
{
    assert(cpustat_reader);
    assert(cpustats_buffer);
    assert(cpustats_count);

    if(cpustat_reader->number_of_cpus == 0 && cpustat_reader_read_number_of_cpu_lines(cpustat_reader) != 0)
        return 1;

    cpustat_reader_prepare_buffers(cpustat_reader, cpustats_buffer, cpustats_count);

    if(cpustat_reader_open_file(cpustat_reader) != 0)
        return 1;

    for(size_t line_number = 0; line_number < cpustat_reader->number_of_cpus; line_number++)
    {
        if(cpustat_reader_read_cpustat_from_file(cpustat_reader, *cpustats_buffer + line_number) < 0)
            return 1;
    }

    if(cpustat_reader_close_file(cpustat_reader) != 0)
        return 1;

    return 0;
}
