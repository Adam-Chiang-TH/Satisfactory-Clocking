#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"

int main(int argc, char *argv[])
{
    // printf("argc = %d\n\n", argc); // DEL
    if (argc < 2 || !run(argc - 1, argv + 1))
        printHelp();
    waitForKey();
    return 0;
}

int run(int argc, char *argv[]) // returns 0 if error
{
    if (argc % 2 != 0) // no option argument with option
        return 0;
    // printf("argc = %d\n\n", argc); // DEL

    double targetInput = -1.0, fullInput = -1.0, fullOutput = -1.0, fullPowerConsumption = -1.0;
    for (int i = 0; i < argc; i += 2)
    {
        // printf("argv[i] = %s\n\n", argv[i]); // DEL
        int operation = parseOption(argv[i]);
        if (!operation)
            return 0;

        switch (operation)
        {
        case 1:
            targetInput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 2:
            fullInput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 3:
            fullOutput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 4:
            fullPowerConsumption = getOptionArgumentDouble(argv[i + 1]);
            break;
        }
    }

    if (targetInput < 0.0 || fullInput < 0.0 || fullOutput < 0.0 || fullPowerConsumption < 0.0)
        return 0;

    double targetClockPercent = targetInput * 100 / fullInput;
    double targetPowerConsumption = fullPowerConsumption * pow(targetClockPercent / 100, 1.321928);

    printf("\n");
    printf("\tTarget clock rate: %lf units", targetClockPercent);
    printf("\n");
    printf("\tTarget output: %lf units", targetClockPercent);
    printf("\n");
    printf("\tTarget power consumption: %lf MW", targetPowerConsumption);
    printf("\n\n");
}

int parseOption(char *option) // returns 0 if erroneous input
{
    if (!strcmp(option, "-t") || !strcmp(option, "--target"))
        return 1;
    else if (!strcmp(option, "-i") || !strcmp(option, "--input"))
        return 2;
    else if (!strcmp(option, "-o") || !strcmp(option, "--output"))
        return 3;
    else if (!strcmp(option, "-p") || !strcmp(option, "--power"))
        return 4;
    return 0;
}

double getOptionArgumentDouble(char *optionArgument)
{
    char *endPtr;
    double ret = strtod(optionArgument, &endPtr);

    if (endPtr != optionArgument)
        return ret;
    return -1.0; // negative is erroneous anyways
}

void printHelp()
{
    printf("PRINT HELP IS RUN!\n\n");
}

void waitForKey()
{
    getchar();
}