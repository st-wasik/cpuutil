#ifndef CPUSTAT_READER_H
#define CPUSTAT_READER_H

#include "cpustat.h"

typedef struct cpustat_reader cpustat_reader_t;

cpustat_reader_t* cpustat_reader_create(void);

void cpustat_reader_destroy(cpustat_reader_t* cpustat_reader);

int cpustat_reader_read_cpustats(cpustat_reader_t* cpustat_reader, cpustat_t** cpustats_buffer, size_t* cpustats_count);

#endif // CPUSTAT_READER_H
