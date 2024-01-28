#include "elapsed_timer.h"

#include <time.h>
#include <assert.h>
#include <memory.h>
#include <stdlib.h>

struct elapsed_timer
{
    struct timespec start_time;
};

elapsed_timer_t* elapsed_timer_create(void)
{
    elapsed_timer_t* elapsed_timer = malloc(sizeof(struct elapsed_timer));
    assert(elapsed_timer);

    memset(elapsed_timer, 0, sizeof(struct elapsed_timer));

    elapsed_timer_restart(elapsed_timer);

    return elapsed_timer;
}

void elapsed_timer_destroy(elapsed_timer_t* elapsed_timer)
{
    assert(elapsed_timer);

    free(elapsed_timer);
}

void elapsed_timer_restart(elapsed_timer_t* elapsed_timer)
{
    assert(elapsed_timer);

    clock_gettime(CLOCK_MONOTONIC, &elapsed_timer->start_time);
}

static struct timespec timespec_subtract(const struct timespec *left, const struct timespec *right)
{
    assert(left);
    assert(right);

    struct timespec diff =
    {
        .tv_sec = left->tv_sec - right->tv_sec,
        .tv_nsec = left->tv_nsec - right->tv_nsec
    };

    if (diff.tv_nsec < 0)
    {
        diff.tv_nsec += 1000000000;
        diff.tv_sec--;
    }

    return diff;
}

long long elapsed_timer_get_elapsed_usec(elapsed_timer_t* elapsed_timer)
{
    struct timespec tp;
    clock_gettime(CLOCK_MONOTONIC, &tp);

    const struct timespec result = timespec_subtract(&tp, &elapsed_timer->start_time);

    return 1000000 * result.tv_sec + 0.001 * result.tv_nsec;
}