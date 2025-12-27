#include "map.h"
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
  double particle_max_random;
  double swarm_max_random;
  double global_best_position[2];
  double global_best_value;
} Swarm;

Swarm swarm;

void initialize_swarm(int particles_count, double weight,
                      double particle_coefficient, double swarm_coefficient,
                      double particle_max_random, double swarm_max_random) {
  swarm.particles_count = particles_count;
  swarm.weight = weight;
  swarm.particle_coefficient = particle_coefficient;
  swarm.swarm_coefficient = swarm_coefficient;
  swarm.particle_max_random = particle_max_random;
  swarm.swarm_max_random = swarm_max_random;
  swarm.particles = (Particle *)malloc(particles_count * sizeof(Particle));
  for (int i = 0; i < particles_count; i++) {
    Particle particle = swarm.particles[i];
    particle.position[0] = rand() % get_map_width();
    particle.position[1] = rand() % get_map_height();
    particle.velocity[0] = (rand() % 3) - 1;
    particle.velocity[1] = (rand() % 3) - 1;
    particle.best_position[0] = swarm.particles[i].position[0];
    particle.best_position[1] = swarm.particles[i].position[1];
    particle.best_value =
        get_map_value(particle.position[0], particle.position[1]);
    if (i == 0 || particle.best_value < swarm.global_best_value) {
      swarm.global_best_value = swarm.particles[i].best_value;
      swarm.global_best_position[0] = particle.best_position[0];
      swarm.global_best_position[1] = particle.best_position[1];
    }
  }
}

void iterate_swarm() {
  for (int i = 0; i < swarm.particles_count; i++) {
    Particle particle = swarm.particles[i];
    double particle_random = ((double)rand() / RAND_MAX) * swarm.particle_max_random;
    double swarm_random = ((double)rand() / RAND_MAX) * swarm.swarm_max_random;
    double map_size[2] = {get_map_width(), get_map_height()};
    for (int d = 0; d < 2; d++) {
      particle.velocity[d] =
          swarm.weight * particle.velocity[d] +
          swarm.particle_coefficient * particle_random *
              (particle.best_position[d] - particle.position[d]) +
          swarm.swarm_coefficient * swarm_random *
              (swarm.global_best_position[d] - particle.position[d]);
      particle.position[d] += particle.velocity[d];
      if (particle.position[d] < 0){
        particle.position[d] = 0.0;
        particle.velocity[d] = 0.0;
      }
      if (particle.position[d] >= map_size[d]) {
        particle.position[d] = (double)(map_size[d] - 1);
        particle.velocity[d] = 0.0;
      }
    }
    double current_value =
        get_map_value(particle.position[0], particle.position[1]);
    if (current_value > particle.best_value) {
      particle.best_value = current_value;
      particle.best_position[0] = particle.position[0];
      particle.best_position[1] = particle.position[1];
    }
    if (current_value > swarm.global_best_value) {
      swarm.global_best_value = current_value;
      swarm.global_best_position[0] = particle.best_position[0];
      swarm.global_best_position[1] = particle.best_position[1];
    }
  }
}

double get_swarm_global_best_value() { return swarm.global_best_value; }

void free_swarm() { free(swarm.particles); }
