#include "map.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
  FILE *map_file = NULL;
  int particles = 30;
  int iterations = 100;
  FILE *config_file = NULL;
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
    } else if (strcmp(argv[i], "-n") == 0 && i + 1 < argc) {
      save_interval = atoi(argv[++i]);
    } else {
      fprintf(stderr, "Blad: Nieznana opcja %s\n", argv[i]);
      return EXIT_FAILURE;
    }
  }

  if (config_file != NULL) {
    fclose(config_file);
  }
  free_map();
  return EXIT_SUCCESS;
}
