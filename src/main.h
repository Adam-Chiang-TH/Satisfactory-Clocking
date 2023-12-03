#pragma once
#ifndef __INCLUDE_MAIN
#define __INCLUDE_MAIN

int run(int argc, char *argv[]); // returns 0 if error

int parseOption(char *option); // returns 0 if erroneous input

double getOptionArgumentDouble(char *optionArgument);

double getDivisor(char *str);

void printHelp();

void waitForKey();

#endif // !__INCLUDE_MAIN