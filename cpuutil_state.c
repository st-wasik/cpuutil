#include "cpuutil_state.h"

#include <assert.h>
#include <memory.h>

cpuutil_state_t* cpuutil_state_create(size_t items_count)
{
    cpuutil_state_t* cpuutil_state = malloc(sizeof(cpuutil_state_t));
    assert(cpuutil_state);

    memset(cpuutil_state, 0, sizeof(struct cpuutil_state));

    cpuutil_state->items_count = items_count;

    cpuutil_state->averages = calloc(items_count, sizeof(average_t));
    assert(cpuutil_state->averages);

    cpuutil_state->last_utilizations = calloc(items_count, sizeof(double));
    assert(cpuutil_state->last_utilizations);

    return cpuutil_state;
}

void cpuutil_state_destroy(cpuutil_state_t* cpuutil_state)
{
    assert(cpuutil_state);

    cpuutil_state->items_count = 0;

    free(cpuutil_state->averages);
    cpuutil_state->averages = NULL;

    free(cpuutil_state->last_utilizations);
    cpuutil_state->last_utilizations = NULL;

    free(cpuutil_state);
}