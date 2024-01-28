#ifndef CPUUTIL_PRINTER_H
#define CPUUTIL_PRINTER_H

#include "parameters.h"
#include "cpuutil_state.h"

typedef struct cpuutil_printer cpuutil_printer_t;

cpuutil_printer_t* cpuutil_printer_create(const parameters_t* parameters);

void cpuutil_printer_destroy(cpuutil_printer_t* cpuutil_printer);

void cpuutil_printer_print(cpuutil_printer_t* cpuutil_printer, const cpuutil_state_t* cpuutil_state);

#endif // CPUUTIL_PRINTER_H