#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int width;
  int height;
  double **data;
} Map;

Map map;

void load_map(FILE *file) {
  fscanf(file, "%d %d", &map.width, &map.height);
  map.data = (double **)malloc(map.height * sizeof(double *));
  for (int y = 0; y < map.height; y++) {
    map.data[y] = (double *)malloc(map.width * sizeof(double));
    for (int x = 0; x < map.width; x++) {
      fscanf(file, "%lf", &map.data[y][x]);
    }
  }
}

double get_map_value(int x, int y) {
  if (x < 0 || x >= map.width || y < 0 || y >= map.height) {
    fprintf(stderr, "Blad: Koordynaty poza mapa (%d, %d)\n", x, y);
    exit(EXIT_FAILURE);
  }
  return map.data[y][x];
}

int get_map_width() {
  return map.width;
}

int get_map_height() {
  return map.height;
}

void free_map() {
  for (int y = 0; y < map.height; y++) {
    free(map.data[y]);
  }
  free(map.data);
}
