#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "main.h"

int main(int argc, char *argv[])
{
    printf("\n");
    if (argc < 2 || !run(argc - 1, argv + 1))
        printHelp();
    waitForKey();
    return 0;
}

int run(int argc, char *argv[]) // returns 0 if error
{
    if (argc % 2 != 0) // no option argument with option
        return 0;

    double targetInput = -1.0, fullInput = -1.0, fullOutput = -1.0, fullPowerConsumption = -1.0;
    for (int i = 0; i < argc; i += 2)
    {
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
    double targetOutput = targetInput * targetClockPercent / 100;
    double targetPowerConsumption = fullPowerConsumption * pow(targetClockPercent / 100, 1.321928);
    double savedPowerConsumption = targetClockPercent * fullPowerConsumption / 100 - targetPowerConsumption;

    printf("\t%-30s%10lf%s", "Target clock percent: ", targetClockPercent, " units per minute");
    printf("\n");
    printf("\t%-30s%10lf%s", "Target output: ", targetOutput, " units per minute");
    printf("\n");
    printf("\t%-30s%10lf%s", "Target power consumption: ", targetPowerConsumption, " MW");
    printf("\n");
    printf("\t%-30s%10lf%s", "Saved power consumption: ", savedPowerConsumption, " MW");
    printf("\n");
    printf("\n");
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

double getOptionArgumentDouble(char *str)
{
    char *endPtr;
    double ret = strtod(str, &endPtr);

    if (!strlen(endPtr))
        return ret;
    else if (endPtr[0] == '/')
    {
        double divisor = getDivisor(endPtr);
        if (divisor < 0)
            return -1.0;
        else
            return ret / divisor;
    }
    return -1.0; // negative is erroneous anyways
}

double getDivisor(char *str)
{
    char *endPtr;
    double ret = strtod(str + 1, &endPtr);
    if (!strlen(endPtr))
        return ret;
    return -1.0;
}

void printHelp()
{
    printf("Arguments:");
    printf("\n");
    printf("\t%-20s%50s", "-t <value>", "Specify the target input units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "--target <value>", "Specify the target input units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "-i <value>", "Specify the fully-clocked input units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "--input <value>", "Specify the fully-clocked input units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "-o <value>", "Specify the fully-clocked output units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "--output <value>", "Specify the fully-clocked output units per minute.");
    printf("\n");
    printf("\t%-20s%50s", "-p <value>", "Specify the fully-clocked power consumption in MW.");
    printf("\n");
    printf("\t%-20s%50s", "--power<value>", "Specify the fully-clocked power consumption in MW.");
    printf("\n");

    printf("\n");
}

void waitForKey()
{
    getchar();
}