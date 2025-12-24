#include <stdio.h>

#ifndef MAP_H
#define MAP_H

void load_map(FILE *file);

double get_map_value(int x, int y);

void free_map();

#endif 
