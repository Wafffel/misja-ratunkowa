#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>

void print_particle_log(FILE *output);

void print_swarm_log(FILE *output);

void print_log(FILE *output, int iteration);

#endif
