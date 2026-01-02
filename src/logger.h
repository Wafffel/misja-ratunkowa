#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void print_csv_header(FILE *output);

void print_log(FILE *output, int iteration);

#endif
