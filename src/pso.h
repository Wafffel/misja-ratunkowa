void initialize_swarm(int particles_count, double weight,
                      double particle_coefficient, double swarm_coefficient,
                      double particle_max_random, double swarm_max_random);

void iterate_swarm();

double get_swarm_global_best_value();

double get_swarm_global_best_x();

double get_swarm_global_best_y();

void free_swarm();
