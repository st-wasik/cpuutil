#ifndef AVERAGE_H
#define AVERAGE_H
#include <stdlib.h>

struct average
{
    double value;
    size_t count;
};

typedef struct average average_t;

void average_add(average_t* average, double value);

#endif // AVERAGE_H   