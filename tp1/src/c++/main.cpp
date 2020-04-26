#include <iostream>
#include <vector>
#include <fstream>
#include "partido.h"
#include "defines.h"
#include "Season.hpp"

using namespace std;

Season parseDat(const string &path);
void saveResult(string outputPath, vector<ranking_t> rankings);

int main(int argc, char* argv[]) {
  int method = stoi(argv[1]);
  string inputPath = argv[2];
  string outputPath = argv[3];

  //Se crea la temporada con los datos de entrada
  Season season = parseDat(inputPath);
  vector<ranking_t> rankings;

  /**
   * 0 => CMM
   * 1 => WP
   * 2 => Own Method
   */
  switch (method) {
    case 0:
      //Genera la matriz C y b para calcular el ranking segun CMM.
      rankings = season.calculateCMMRanking();
      break;
  }

  //Exporta el resultado al archivo pasado por parametro
  saveResult(outputPath, rankings);

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

/**
 * Export ranking table in outputPath.
 * @param outputPath
 * @param rankings
 */
void saveResult(string outputPath, vector<ranking_t> rankings) {
  ofstream file(outputPath);
  file.precision(FILE_PRESITION);
  for (int i = 0; i < rankings.size(); ++i) {
    file << rankings[i] << endl;
  }
  file.close();
}
