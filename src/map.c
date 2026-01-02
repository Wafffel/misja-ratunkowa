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
  if (map.data == NULL) {
    fprintf(stderr, "Blad: Nie udalo sie zaalokowac pamieci dla mapy\n");
    exit(EXIT_FAILURE);
  }
  for (int y = 0; y < map.height; y++) {
    map.data[y] = (double *)malloc(map.width * sizeof(double));
    if (map.data[y] == NULL) {
      fprintf(stderr, "Blad: Nie udalo sie zaalokowac pamieci dla wiersza mapy\n");
      exit(EXIT_FAILURE);
    }
    for (int x = 0; x < map.width; x++) {
      fscanf(file, "%lf", &map.data[y][x]);
    }
  }
}

double get_map_value(double x, double y) {
  int ix = (int)x;
  int iy = (int)y;
  if (ix < 0 || ix >= map.width || iy < 0 || iy >= map.height) {
    fprintf(stderr, "Blad: Koordynaty poza mapa (%d, %d)\n", ix, iy);
    exit(EXIT_FAILURE);
  }
  return map.data[iy][ix];
}

int get_map_width() { return map.width; }

int get_map_height() { return map.height; }

void free_map() {
  for (int y = 0; y < map.height; y++) {
    free(map.data[y]);
  }
  free(map.data);
}
