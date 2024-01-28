#include "parameters.h"

#include <stdio.h>
#include <assert.h>
#include <getopt.h>
#include <stdlib.h>
#include <ctype.h>

#define SEC_TO_MICROSEC_FACTOR 1000000.0

static void parameters_set_defaults(parameters_t* parameters)
{
    assert(parameters);

    parameters->sleep_interval_usec = 1 * SEC_TO_MICROSEC_FACTOR;
    parameters->print_average_utilization = 1;
    parameters->print_current_utilization = 1;
}

int parameters_parse(parameters_t* parameters, int argc, char **argv)
{
    assert(parameters);

    parameters_set_defaults(parameters);

    char c = 0;

    while ((c = getopt (argc, argv, "AChs:")) != -1)
    {
        switch(c)
        {
        case 'A':
            parameters->print_average_utilization = 0;
            break;
        case 'C':
            parameters->print_current_utilization = 0;
            break;
        case 'h':
            parameters->print_help = 1;
            break;
        case 's':
            parameters->sleep_interval_usec = strtod(optarg, NULL) * SEC_TO_MICROSEC_FACTOR;
            break;
        case '?':
            if(optopt == 's')
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if(isprint(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else 
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            return 1;
        default:
            abort();
        }
    }

    if(parameters->print_average_utilization == 0 && parameters->print_current_utilization == 0)
    {
        fprintf(stderr, "Arguments 'A' and 'C' cannot be used together.\n");

        return 1;
    }

    if(optind < argc)
    {
        for (int index = optind; index < argc; index++)
            fprintf(stderr, "Non-option argument %s\n", argv[index]);

        return 1;
    }

  return 0;
}

void parameters_print_help(void)
{
    fprintf(stderr, 
        "cpuutil - print CPU utilization percentage over time\n"
        "\n"
        "Example: cpuutil [-AChs]\n"
        "\n"
        "Parameters:\n"
        "-A\tdo not calculate and do not print average utilization\n"
        "-C\tdo not print current utilization\n"
        "-h\tprint this message and exit\n"
        "-s\tsleep interval in seconds, default 1.0\n"
    );
}