#pragma once
#ifndef __INCLUDE_MAIN
#define __INCLUDE_MAIN

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int run(int argc, char *argv[]); // returns 0 if error

int parseOption(char *option); // returns 0 if erroneous input

double getOptionArgumentDouble(char *optionArgument);

double getDivisor(char *str);

void printHelp(char *str);

#endif // !__INCLUDE_MAIN