#include "include/gtest/gtest.h"
#include <fstream>
#include <dirent.h>
#include <cmath>
#include "string"
#include "expecteds.h"
#include "../src/c++/Season.hpp"

DIR *dpdf;
struct dirent *epdf;

vector<string> getCatedraTests();

vector<ranking_t> getExpected(string expectedFile, int cantEquipos);

TEST(seasonGenerateMatrixTests, catedraTests) {
  ofstream archivo("exps/comparacionCuantitativo.csv", fstream::in | fstream::out | fstream::trunc);
  archivo << "id, test, cantEquipos, diff" << endl;
  archivo.precision(14);
  archivo << std::fixed;

  vector<string> files = getCatedraTests();
  for (int i = 0; i < files.size(); i++) {
    string path = files[i];
    Season season = Season::parseDat(path + ".in");

    //Calculo el score con el metodo de CMM
    vector<ranking_t> rankings = season.calculateCMMRanking();
    //Busco los resultados esperados
    vector<ranking_t> expectedRankings = getExpected(path + ".expected", season.getCantEquipos());

    EXPECT_VECTOR_FLOATS_NEARLY_EQ(rankings, expectedRankings, precision);

    ranking_t error = 0;
    for (int j = 0; j < rankings.size(); ++j) {
      error += abs(rankings[j] - expectedRankings[j]);
    }
    error /= rankings.size();

    archivo << i << ", " << path.substr(path.find_last_of('/') + 1) << ", " << season.getCantEquipos()  << ", " << error << endl;

  }
}

vector<ranking_t> getExpected(string expectedFile, int cantEquipos) {
  ifstream file(expectedFile);
  vector<ranking_t> expectedRankings;
  for (int i = 0; i < cantEquipos; i++) {
    ranking_t score;
    file >> score;
    expectedRankings.push_back(score);
  }
  return expectedRankings;
}

vector<string> getCatedraTests() {
  vector<const char *> dirs = {"tests/", "tests/test_completos/"};
  vector<string> files;
  for (const char *path : dirs) {
    dpdf = opendir(path);
    if (dpdf != NULL) {
      epdf = readdir(dpdf);
      while (epdf) {
        string file = epdf->d_name;
        if (strstr(epdf->d_name, ".in")) {
          //Guardo el nombre de todos los files en el directorio sin extension
          string fileName = path + file.substr(0, file.find(".in"));
          files.push_back(fileName);
        }
        epdf = readdir(dpdf);
      }
    }
    closedir(dpdf);
  }
  return files;
}
