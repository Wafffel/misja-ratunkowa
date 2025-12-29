void initialize_swarm(int particles_count, double weight,
                      double particle_coefficient, double swarm_coefficient,
                      double particle_max_random, double swarm_max_random);

void iterate_swarm();

double get_swarm_global_best_value();

double get_swarm_global_best_x();

double get_swarm_global_best_y();

int get_swarm_particles_count();

double get_particle_x(int index);

double get_particle_y(int index);

double get_particle_best_x(int index);

double get_particle_best_y(int index);

void free_swarm();
