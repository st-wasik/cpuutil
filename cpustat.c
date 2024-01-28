#include "cpustat.h"
#include <assert.h>

void cpustat_subtract(cpustat_t* destination, const cpustat_t* left, const cpustat_t* right)
{
    destination->user = left->user - right->user;
    destination->nice = left->nice - right->nice;
    destination->system = left->system - right->system;
    destination->idle = left->idle - right->idle;
    destination->iowait = left->iowait - right->iowait;
    destination->irq = left->irq - right->irq;
    destination->softirq = left->softirq - right->softirq;
    destination->steal = left->steal - right->steal;
    destination->guest = left->guest - right->guest;
    destination->guest_nice = left->guest_nice - right->guest_nice;
}

double cpustat_calculate_utilization(const cpustat_t* cpustat)
{
    const long long total = cpustat->user
        + cpustat->nice
        + cpustat->system
        + cpustat->idle
        + cpustat->iowait
        + cpustat->irq
        + cpustat->softirq
        + cpustat->steal
        + cpustat->guest
        + cpustat->guest_nice;

    if(total == 0)
        return -1.0;

    return (double) (total - cpustat->idle) / total;
}