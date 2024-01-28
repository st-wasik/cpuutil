#ifndef CPUUTIL_STATE_H
#define CPUUTIL_STATE_H

#include <stdlib.h>

#include "cpustat.h"
#include "average.h"

struct cpuutil_state
{
    size_t step_number;
    size_t items_count;
    average_t* averages;
    double* last_utilizations;
    char is_utilization_invalid;
    long long execution_time_usec;
};

typedef struct cpuutil_state cpuutil_state_t;

cpuutil_state_t* cpuutil_state_create(size_t items_count);

void cpuutil_state_destroy(cpuutil_state_t* cpuutil_state);

#endif // CPUUTIL_STATE_H