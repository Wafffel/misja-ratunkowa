#include "map.h"
#include "pso.h"
#include <stdio.h>

void print_particle_log(FILE *output) {
  int particle_count = get_swarm_particles_count();
  fprintf(
      output,
      "Numer, X, Y, Wartosc, Najlepszy X, Najlepszy Y, Najlepsza wartosc\n");
  for (int i = 0; i < particle_count; i++) {
    double x = get_particle_x(i);
    double y = get_particle_y(i);
    double value = get_map_value(x, y);
    double best_x = get_particle_best_x(i);
    double best_y = get_particle_best_y(i);
    double best_value = get_map_value(best_x, best_y);
    fprintf(output, "%d, %.2f, %.2f, %.2f, %.2f, %.2f, %.2f\n", i, x, y, value,
            best_x, best_y, best_value);
  }
}

void print_swarm_log(FILE *output) {
  double global_best_x = get_swarm_global_best_x();
  double global_best_y = get_swarm_global_best_y();
  double global_best_value = get_swarm_global_best_value();
  fprintf(output, "Najlepszy X roju, Najlepszy Y roju, Najlepsza wartosc roju\n");
  fprintf(output, "%.2f, %.2f, %.2f\n", global_best_x, global_best_y,
          global_best_value);
}

void print_log(FILE *output, int iteration) {
  fprintf(output, "Iteracja: %d\n", iteration);
  print_swarm_log(output);
  print_particle_log(output);
}
