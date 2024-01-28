#include "average.h"

void average_add(average_t* average, double value)
{
    average->value = ((average->value * average->count) + value) / (average->count + 1);
    average->count++;
}