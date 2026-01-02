#include "pso.h"
#include <stdio.h>

static int header_printed = 0;

void print_csv_header(FILE *output) {
  fprintf(output, "iteracja, x, y\n");
  header_printed = 1;
}

void print_log(FILE *output, int iteration) {
  if (!header_printed) {
    print_csv_header(output);
  }
  int particle_count = get_swarm_particles_count();
  for (int i = 0; i < particle_count; i++) {
    double x = get_particle_x(i);
    double y = get_particle_y(i);
    fprintf(output, "%d, %lf, %lf\n", iteration, x, y);
  }
}
