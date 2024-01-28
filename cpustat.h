#ifndef CPUSTAT_H
#define CPUSTAT_H
#include <stdio.h>

typedef struct  
{
    char name[8];
    unsigned long long user;
    unsigned long long nice;
    unsigned long long system;
    unsigned long long idle;
    unsigned long long iowait;
    unsigned long long irq;
    unsigned long long softirq; 
    unsigned long long steal;
    unsigned long long guest; 
    unsigned long long guest_nice;
} cpustat_t;

void cpustat_subtract(cpustat_t* destination, const cpustat_t* left, const cpustat_t* right);

double cpustat_calculate_utilization(const cpustat_t* cpustat);

#endif // CPUSTAT_H