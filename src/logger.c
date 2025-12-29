#include <stdio.h>
#include "pso.h"
#include "map.h"

void print_log(FILE *output) {
  int particle_count = get_swarm_particles_count();
  fprintf(output, "Particle Count: %d\n", particle_count);
  fprintf(output, "Number, X, Y, Value, Best X, Best Y, Best Value\n");
  for (int i = 0; i < particle_count; i++) {
    double x = get_particle_x(i);
    double y = get_particle_y(i);
    double value = get_map_value(x, y);
    double best_x = get_particle_best_x(i);
    double best_y = get_particle_best_y(i);
    double best_value = get_map_value(x, y);
    fprintf(output, "%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", i, x, y, value,
            best_x, best_y, best_value);
  }
}
