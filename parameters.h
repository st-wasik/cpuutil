#ifndef PARAMETERS_H
#define PARAMETERS_H

struct parameters
{
    char print_average_utilization;
    char print_current_utilization;
    char print_help;
    long long sleep_interval_usec;
};

typedef struct parameters parameters_t;

int parameters_parse(parameters_t* parameters, int argc, char **argv);

void parameters_print_help(void);

#endif // PARAMETERS_H