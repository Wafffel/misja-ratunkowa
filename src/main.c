#include "map.h"
#include "pso.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
  srand(time(NULL));
  FILE *map_file = NULL;
  int particles = 30;
  int iterations = 100;
  FILE *config_file = NULL;
  double weight = 0.5;
  double particle_coefficient = 1.5;
  double swarm_coefficient = 1.5;
  double particle_max_random = 1.0;
  double swarm_max_random = 1.0;
  int save_interval = 0;
  char *help_messge = "Uzycie: %s <plik_mapy> [opcje]\n"
                      "Opcje:\n"
                      "  -h, --help       Wyswietl ta pomoc\n"
                      "  -p               liczba czastek (domyslnie 30)\n"
                      "  -i               liczba iteracji (domyslnie 100)\n"
                      "  -c               sciezka do pliku konfiguracyjnego\n"
                      "  -n               co ktora iteracje zapis postepow "
                      "(domyslnie 0 - brak zapisu)\n";

  if (argc < 2) {
    fprintf(stderr, help_messge, argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf(help_messge, argv[0]);
    return EXIT_SUCCESS;
  }

  map_file = fopen(argv[1], "r");
  if (map_file == NULL) {
    fprintf(stderr, "Blad: Nie mozna otworzyc pliku mapy %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  load_map(map_file);
  fclose(map_file);

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf(help_messge, argv[0]);
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
      particles = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      iterations = atoi(argv[++i]);
    } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
      config_file = fopen(argv[++i], "r");
      if (config_file == NULL) {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku konfiguracyjnego %s\n",
                argv[i]);
        return EXIT_FAILURE;
      }
      fscanf(config_file, "%lf %lf %lf %lf %lf", &weight, &particle_coefficient,
             &particle_max_random, &swarm_coefficient, &swarm_max_random);
      fclose(config_file);
    } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
      save_interval = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Blad: Nieznana opcja %s\n", argv[i]);
      return EXIT_FAILURE;
    }
  }

  initialize_swarm(particles, weight, particle_coefficient, swarm_coefficient,
                   particle_max_random, swarm_max_random);
  for (int iter = 0; iter < iterations; iter++) {
    iterate_swarm();
    if (save_interval > 0 && (iter + 1) % save_interval == 0) {
      printf("Iteracja %d: Najlepsza wartosc = %lf na pozycji (%lf, %lf)\n",
             iter + 1, get_swarm_global_best_value(), get_swarm_global_best_x(),
             get_swarm_global_best_y());
    }
  }
  printf("Koniec: Najlepsza wartosc = %lf na pozycji (%lf, %lf)\n",
         get_swarm_global_best_value(), get_swarm_global_best_x(),
         get_swarm_global_best_y());

  free_map();
  return EXIT_SUCCESS;
}
