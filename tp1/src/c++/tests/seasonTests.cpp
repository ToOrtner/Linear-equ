#include "include/gtest/gtest.h"
#include <fstream>
#include <dirent.h>
#include "string"
#include "../Season.hpp"

DIR *dpdf;
struct dirent *epdf;

vector<string> getCatedraTests();
Season getSeason(string testFile);
vector<ranking_t> getExpected(string expectedFile, int cantEquipos);

TEST(seasonGenerateMatrixTests, catedraTests) {
  vector<string> files = getCatedraTests();
  for (int i = 0; i < 1; i++) {
    string path = "../tests/" + files[i] + ".in";
    Season season = getSeason(path + ".in");

    //Calculo el score con el metodo de CMM
    vector<ranking_t> rankings = season.calculateCMMRanking();
    //Busco los resultados esperados
    vector<ranking_t> expectedRankings = getExpected(path + ".expected", season.getCantEquipos());

    std::sort(rankings.begin(), rankings.end());
    std::sort(expectedRankings.begin(), expectedRankings.end());

    cout.precision(FILE_PRESITION);
    for (int j = 0; j < rankings.size(); ++j) {
      cout << "resultado: " << rankings[j] << "; esperado: " << expectedRankings[j] << endl;
    }

  }

  assert(true);
}

vector<ranking_t> getExpected(string expectedFile, int cantEquipos) {
  ifstream file (expectedFile);
  vector<ranking_t> expectedRankings;
  for (int i = 0; i < cantEquipos; i++) {
    ranking_t score;
    file >> score;
    expectedRankings.push_back(score);
  }
  return expectedRankings;
}

Season getSeason(string testFile) {
  ifstream file (testFile);
  int cantPartidos, cantEquipos;
  file >> cantEquipos >> cantPartidos;

  vector<partido> partidos = vector<partido>();
  string fecha, equipo1, equipo2;
  int p1, p2;
  int j = 0;
  while(j < cantPartidos && file >> fecha >> equipo1 >> p1 >> equipo2 >> p2) {
    partido p(fecha, equipo1, p1, equipo2, p2);
    partidos.push_back(p);
    j++;
  }
  file.close();
  return Season(cantPartidos, cantEquipos, partidos);
}

vector<string> getCatedraTests() {
  vector<string> files;
  dpdf = opendir("../tests");
  if (dpdf != NULL) {
    epdf = readdir(dpdf);
    while (epdf) {
      string file = epdf->d_name;
      if(strstr(epdf->d_name, ".in")) {
        //Guardo el nombre de todos los files en el directorio sin extension
        string fileName = file.substr(0, file.find(".in"));
        files.push_back(fileName);
      }
      epdf = readdir(dpdf);
    }
  }
  closedir(dpdf);
  return files;
}
