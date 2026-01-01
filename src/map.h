#ifndef MAP_H
#define MAP_H

#include <stdio.h>

void load_map(FILE *file);

double get_map_value(double x, double y);

int get_map_width();

int get_map_height();

void free_map();

#endif
