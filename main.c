#include <stdio.h>
#include <stdlib.h>
#include <sys/param.h>
#include <unistd.h>
#include <limits.h>
#include <memory.h>

#include "cpustat.h"
#include "average.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <assert.h>

#include "cpuutil.h"
#include "parameters.h"

int main(int argc, char **argv)
{
    parameters_t parameters;

    if(parameters_parse(&parameters, argc, argv) != 0)
        return 1;

    if(parameters.print_help)
    {
        parameters_print_help();
        return 0;
    }

    return cpuutil_run(&parameters);
}

