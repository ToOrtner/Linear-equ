#include <iostream>
#include <vector>
#include <fstream>
#include "partido.h"
#include "defines.h"
#include "Season.hpp"

using namespace std;


Season parseDat(const string &path);

int main(int argc, char* argv[]) {
  int method = stoi(argv[1]);
  string inputPath = argv[2];
  string outputPath = argv[3];

  Season season = parseDat(inputPath);

  return 0;
}

/**
 * Read the file and generate array with all games
 * @param path
 * @return
 */
Season parseDat(const string &path) {
  ifstream file (path);
  nat cantPartidos, cantEquipos;
  file >> cantEquipos >> cantPartidos;

  vector<partido> partidos = vector<partido>();
  string fecha, equipo1, equipo2;
  int p1, p2;
  nat i = 0;
  while(i < cantPartidos && file >> fecha >> equipo1 >> p1 >> equipo2 >> p2) {
    partido p(fecha, equipo1, p1, equipo2, p2);
    partidos.push_back(p);
    i++;
  }
  file.close();

  return Season(cantPartidos, cantEquipos, partidos);
}
