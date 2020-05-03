#include <vector>
#include <fstream>
#include "partido.h"
#include "defines.h"
#include "Season.hpp"

using namespace std;
void saveResult(string outputPath, vector<ranking_t> rankings);

int main(int argc, char* argv[]) {
  string inputPath = argv[1];
  string outputPath = argv[2];
  int method = stoi(argv[3]);

  //Se crea la temporada con los datos de entrada
  Season season = Season::parseDat(inputPath);
  vector<ranking_t> rankings;

  /**
   * 0 => CMM
   * 1 => WP
   * 2 => Own Method
   */
  switch (method) {
    case 0:
      // Genera la matriz C y b para calcular el ranking segun CMM.
      rankings = season.calculateCMMRanking();
      break;
    case 1:
      // Hace el calculo de ganados/jugados.
      rankings = season.calculateWPRanking();
      break;
    case 2:
      // Hace el calculo de (1 + ganados)/(2 + jugados).
      rankings = season.calculateWPRankingWithLaplace();
      break;
  }

  //Exporta el resultado al archivo pasado por parametro
  saveResult(outputPath, rankings);

  return 0;
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