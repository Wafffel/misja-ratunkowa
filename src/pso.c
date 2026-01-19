#include "map.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double position[2];
  double velocity[2];
  double best_position[2];
  double best_value;
} Particle;

typedef struct {
  Particle *particles;
  int particles_count;
  double weight;
  double particle_coefficient;
  double swarm_coefficient;
  double global_best_position[2];
  double global_best_value;
} Swarm;

Swarm swarm;

void initialize_swarm(int particles_count, double weight,
                      double particle_coefficient, double swarm_coefficient) {
  swarm.particles_count = particles_count;
  swarm.weight = weight;
  swarm.particle_coefficient = particle_coefficient;
  swarm.swarm_coefficient = swarm_coefficient;
  swarm.particles = (Particle *)malloc(particles_count * sizeof(Particle));
  if (swarm.particles == NULL) {
    fprintf(stderr, "Blad: Nie udalo sie zaalokowac pamieci dla czastek\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < particles_count; i++) {
    Particle *particle = &swarm.particles[i];
    particle->position[0] = rand() % get_map_width();
    particle->position[1] = rand() % get_map_height();
    particle->velocity[0] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    particle->velocity[1] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    particle->best_position[0] = particle->position[0];
    particle->best_position[1] = particle->position[1];
    particle->best_value =
        get_map_value(particle->position[0], particle->position[1]);
    if (i == 0 || particle->best_value < swarm.global_best_value) {
      swarm.global_best_value = particle->best_value;
      swarm.global_best_position[0] = particle->best_position[0];
      swarm.global_best_position[1] = particle->best_position[1];
    }
  }
}

void iterate_swarm() {
  for (int i = 0; i < swarm.particles_count; i++) {
    Particle *particle = &swarm.particles[i];
    double particle_random = ((double)rand() / RAND_MAX);
    double swarm_random = ((double)rand() / RAND_MAX);
    double map_size[2] = {get_map_width(), get_map_height()};
    for (int d = 0; d < 2; d++) {
      particle->velocity[d] =
          swarm.weight * particle->velocity[d] +
          swarm.particle_coefficient * particle_random *
              (particle->best_position[d] - particle->position[d]) +
          swarm.swarm_coefficient * swarm_random *
              (swarm.global_best_position[d] - particle->position[d]);
      particle->position[d] += particle->velocity[d];
      if (particle->position[d] < 0) {
        particle->position[d] = 0.0;
        particle->velocity[d] = 0.0;
      }
      if (particle->position[d] >= map_size[d]) {
        particle->position[d] = (double)(map_size[d] - 1);
        particle->velocity[d] = 0.0;
      }
    }
    double current_value =
        get_map_value(particle->position[0], particle->position[1]);
    if (current_value > particle->best_value) {
      particle->best_value = current_value;
      particle->best_position[0] = particle->position[0];
      particle->best_position[1] = particle->position[1];
    }
    if (current_value > swarm.global_best_value) {
      swarm.global_best_value = current_value;
      swarm.global_best_position[0] = particle->best_position[0];
      swarm.global_best_position[1] = particle->best_position[1];
    }
  }
}

double get_swarm_global_best_value() { return swarm.global_best_value; }

double get_swarm_global_best_x() { return swarm.global_best_position[0]; }

double get_swarm_global_best_y() { return swarm.global_best_position[1]; }

int get_swarm_particles_count() { return swarm.particles_count; }

double get_particle_x(int index) { return swarm.particles[index].position[0]; }

double get_particle_y(int index) { return swarm.particles[index].position[1]; }

double get_particle_best_x(int index) {
  return swarm.particles[index].best_position[0];
}

double get_particle_best_y(int index) {
  return swarm.particles[index].best_position[1];
}

void free_swarm() { free(swarm.particles); }
