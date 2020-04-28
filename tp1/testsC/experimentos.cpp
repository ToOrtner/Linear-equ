#include <chrono>
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <fstream>
#include "../src/c++/defines.h"
#include "../src/c++/partido.h"
#include "../src/c++/Season.hpp"

static const string FILE_OUTPUT_DELTA_PREFIX =  "exps/output_";
void correrCMM();

int main() {
  correrCMM();
  return 1;
}

void correrCMM() {
  Season season = Season::parseDat("data/atp_matches_2015.dat");
  string file_name = FILE_OUTPUT_DELTA_PREFIX + to_string(season.getCantPartidos()) + "_" + to_string(season.getCantEquipos()) + ".csv";

  //Output file
  ofstream outputFile;
  outputFile.open (file_name, fstream::in | fstream::out | fstream::trunc);
  outputFile << "tiempo" << endl;

  //Contabilizo el tiempo por las dudas
  auto start = chrono::steady_clock::now();
  season.calculateCMMRanking();
  auto end = chrono::steady_clock::now();

  auto timeElapsed = end - start;
  outputFile << chrono::duration <double, milli>(timeElapsed).count() << endl;

  outputFile.close();
}