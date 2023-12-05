#include "main.h"

int main(int argc, char *argv[])
{
    printf("\n");
    if (argc < 2 || !run(argc - 1, argv + 1))
        printHelp(argv[0]);
    return 0;
}

int run(int argc, char *argv[]) // returns 0 if error
{
    if (argc % 2 != 0) // no option argument with option
        return 0;

    double targetInput = -1.0, fullInput = -1.0, fullOutput = -1.0, fullPowerConsumption = -1.0;
    int totalMachines = 1;
    for (int i = 0; i < argc; i += 2)
    {
        int operation = parseOption(argv[i]);
        if (!operation)
            return 0;

        switch (operation)
        {
        case 1:
            fullInput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 2:
            fullOutput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 3:
            targetInput = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 4:
            fullPowerConsumption = getOptionArgumentDouble(argv[i + 1]);
            break;
        case 11:
            totalMachines = round(getOptionArgumentDouble(argv[i + 1]));
            break;
        }
    }

    if (targetInput < 0.0 || fullInput < 0.0 || fullOutput < 0.0 || fullPowerConsumption < 0.0)
        return 0;

    double targetClockPercent = targetInput * 100 / fullInput;
    double targetOutput = targetInput * targetClockPercent / 100;
    double targetPowerConsumption = fullPowerConsumption * pow(targetClockPercent / 100, 1.321928);
    double savedPowerConsumption = targetClockPercent * fullPowerConsumption / 100 - targetPowerConsumption;

    printf("\t%-30s%10lf%s", "Target clock speed: ", targetClockPercent, " units per minute");
    printf("\n");
    printf("\t%-30s%10lf%s", "Target output: ", targetOutput, " units per minute");
    printf("\n");
    printf("\t%-30s%10lf%s", "Target power consumption: ", targetPowerConsumption, " MW");
    printf("\n");
    printf("\t%-30s%10lf%s", "Saved power consumption: ", savedPowerConsumption, " MW per machine");
    printf("\n");
    if (totalMachines > 1)
    {
        printf("\n");
        printf("\t%-30s%10lf%s%d%s", "Total power consumption: ", targetPowerConsumption * (double)totalMachines, " MW for all ", totalMachines, " machines");
        printf("\n");
        printf("\t%-30s%10lf%s%d%s", "Total saved power consumption: ", savedPowerConsumption * (double)totalMachines, " MW for all ", totalMachines, " machines");
        printf("\n");
    }
    printf("\n");
}

int parseOption(char *option) // returns 0 if erroneous input
{
    if (!strcmp(option, "-i") || !strcmp(option, "--input"))
        return 1;
    else if (!strcmp(option, "-o") || !strcmp(option, "--output"))
        return 2;
    else if (!strcmp(option, "-t") || !strcmp(option, "--target"))
        return 3;
    else if (!strcmp(option, "-p") || !strcmp(option, "--power"))
        return 4;
    else if (!strcmp(option, "-m") || !strcmp(option, "--machines"))
        return 11;
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

void printHelp(char *str)
{
    printf("Usage: %s <ARGUMENTS>", str);
    printf("\n");
    printf("Mandatory arguments:");
    printf("\n");
    printf("\t%-30s%50s", "-i <VALUE>, --input <VALUE>", "Fully-clocked input units per minute.");
    printf("\n");
    printf("\t%-30s%50s", "-o <VALUE>, --output <VALUE>", "Fully-clocked output units per minute.");
    printf("\n");
    printf("\t%-30s%50s", "-t <VALUE>, --target <VALUE>", "Target input units per minute.");
    printf("\n");
    printf("\t%-30s%50s", "-p <VALUE>, --power <VALUE>", "Fully-clocked power consumption in MW.");
    printf("\n");
    printf("\n");
    printf("Options:");
    printf("\n");
    printf("\t%-30s%50s", "-m <VALUE>, --machines <VALUE>", "Total number of machines.");
    printf("\n");
    printf("\n");
    printf("Example:");
    printf("\n");
    printf("\tAt 100%% clock speed, a constructor requires 37.5 raw quartz per minute to output 22.5 quartz crystals per minute.");
    printf("\n");
    printf("\tAn input Mk.1 conveyor belt is split evenly to 3 constructors.");
    printf("\n");
    printf("Example usage:");
    printf("\n");
    printf("\t%s -i 37.5 -o 22.5 -t 60/3 -p 4 -m 3", str);
    printf("\n");
    printf("\n");
}