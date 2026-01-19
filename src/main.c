#include "logger.h"
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
  double particle_coefficient = 1.0;
  double swarm_coefficient = 1.0;
  int save_interval = 0;
  FILE *output_file = stdout;
  char *help_message = "Uzycie: %s <plik_mapy> [opcje]\n"
                       "Opcje:\n"
                       "  -h, --help       Wyswietl ta pomoc\n"
                       "  -p               liczba czastek (domyslnie 30)\n"
                       "  -i               liczba iteracji (domyslnie 100)\n"
                       "  -c               sciezka do pliku konfiguracyjnego\n"
                       "  -n               co ktora iteracje zapis postepow "
                       "(domyslnie 0 - brak zapisu)\n"
                       "  -o               output file (domyslnie stdout)\n";

  if (argc < 2) {
    fprintf(stderr, help_message, argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    printf(help_message, argv[0]);
    return EXIT_SUCCESS;
  }

  for (int i = 2; i < argc; i++) {
    if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
      printf(help_message, argv[0]);
      return EXIT_SUCCESS;
    } else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
      particles = atoi(argv[++i]);
      if (particles <= 0) {
        fprintf(stderr, "Blad: Liczba czastek musi byc wieksza od 0\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
      iterations = atoi(argv[++i]);
      if (iterations <= 0) {
        fprintf(stderr, "Blad: Liczba iteracji musi byc wieksza od 0\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp(argv[i], "-c") == 0 && i + 1 < argc) {
      config_file = fopen(argv[++i], "r");
      if (config_file == NULL) {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku konfiguracyjnego %s\n",
                argv[i]);
        return EXIT_FAILURE;
      }
      fscanf(config_file, "%lf %lf %lf", &weight, &particle_coefficient,
             &swarm_coefficient);
      fclose(config_file);
    } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
      save_interval = atoi(argv[++i]);
      if (save_interval < 0) {
        fprintf(stderr, "Blad: Interwal zapisu musi byc nieujemny\n");
        return EXIT_FAILURE;
      }
    } else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
      output_file = fopen(argv[++i], "w");
      if (output_file == NULL) {
        fprintf(stderr, "Blad: Nie mozna otworzyc pliku wyjsciowego %s\n",
                argv[i]);
        return EXIT_FAILURE;
      }
    } else {
      fprintf(stderr, "Blad: Nieznana opcja %s\n", argv[i]);
      return EXIT_FAILURE;
    }
  }

  map_file = fopen(argv[1], "r");
  if (map_file == NULL) {
    fprintf(stderr, "Blad: Nie mozna otworzyc pliku mapy %s\n", argv[1]);
    return EXIT_FAILURE;
  }
  load_map(map_file);
  fclose(map_file);

  initialize_swarm(particles, weight, particle_coefficient, swarm_coefficient);
  for (int iter = 0; iter < iterations; iter++) {
    if (save_interval > 0 && iter % save_interval == 0) {
      print_log(output_file, iter);
    }
    iterate_swarm();
  }
  printf("Koniec: Najlepsza wartosc = %lf na pozycji (%d, %d)\n",
         get_swarm_global_best_value(), (int)get_swarm_global_best_x(),
         (int)get_swarm_global_best_y());

  free_map();
  free_swarm();
  if (output_file != stdout) {
    fclose(output_file);
  }
  return EXIT_SUCCESS;
}
