#include <stdlib.h>

int main(int argc, char *argv[]) {
  char *help_messge = "Uzycie: %s <plik_mapy> [opcje]\n"
                      "Opcje:\n"
                      "  -h, --help       Wyswietl ta pomoc\n"
                      "  -p               liczba czastek (domyslnie 30)\n"
                      "  -i               liczba iteracji (domyslnie 100)\n"
                      "  -c               sciezka do pliku konfiguracyjnego\n"
                      "  -n               co ktora iteracje zapis postepow (domyslnie 0 - brak zapisu)\n"; 
  return EXIT_SUCCESS;
}
