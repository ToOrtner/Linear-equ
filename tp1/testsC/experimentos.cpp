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
void correrWP();
void correrLaplace();
void compararTiempos();

int main() {
  /*
  correrCMM();
  correrWP();
  correrLaplace();*/

  compararTiempos();
  return 1;
}

void correrCMM() {
  Season season = Season::parseDat("data/atp_matches_2015.dat");
  string file_name = FILE_OUTPUT_DELTA_PREFIX + "_CMM_" + to_string(season.getCantPartidos()) + "_" + to_string(season.getCantEquipos()) + ".csv";

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

void correrWP() {
  Season season = Season::parseDat("data/atp_matches_2015.dat");
  string file_name = FILE_OUTPUT_DELTA_PREFIX + "_WP_" + to_string(season.getCantPartidos()) + "_" + to_string(season.getCantEquipos()) + ".csv";

  //Output file
  ofstream outputFile;
  outputFile.open (file_name, fstream::in | fstream::out | fstream::trunc);
  outputFile << "tiempo" << endl;

  //Contabilizo el tiempo por las dudas
  auto start = chrono::steady_clock::now();
  season.calculateWPRanking();
  auto end = chrono::steady_clock::now();

  auto timeElapsed = end - start;
  outputFile << chrono::duration <double, milli>(timeElapsed).count() << endl;

  outputFile.close();
}

void correrLaplace() {
  Season season = Season::parseDat("data/atp_matches_2015.dat");
  string file_name = FILE_OUTPUT_DELTA_PREFIX + "_Laplace_" + to_string(season.getCantPartidos()) + "_" + to_string(season.getCantEquipos()) + ".csv";

  //Output file
  ofstream outputFile;
  outputFile.open (file_name, fstream::in | fstream::out | fstream::trunc);
  outputFile << "tiempo" << endl;

  //Contabilizo el tiempo por las dudas
  auto start = chrono::steady_clock::now();
  season.calculateWPRankingWithLaplace();
  auto end = chrono::steady_clock::now();

  auto timeElapsed = end - start;
  outputFile << chrono::duration <double, milli>(timeElapsed).count() << endl;

  outputFile.close();
}

void compararTiempos(){
  ofstream archivo;  // objeto de la clase ofstream
  archivo.open("/comparacionTiempos.csv");
  archivo << "n,CMM,WP,Laplace" << endl;
  Season season = Season::parseDat("data/atp_matches_2015.dat");

  nat n = season.getCantPartidos();

  auto time_start_CMM = std::chrono::steady_clock::now();
  season.calculateCMMRanking();
  auto time_end_CMM = std::chrono::steady_clock::now();
  auto timeCMM = chrono::duration_cast<std::chrono::milliseconds>(time_end_CMM - time_start_CMM).count();

  auto time_start_WP = std::chrono::steady_clock::now();
  season.calculateWPRanking();
  auto time_end_WP = std::chrono::steady_clock::now();
  auto timeWP = chrono::duration_cast<std::chrono::milliseconds>(time_end_WP - time_start_WP).count();

  auto time_start_Lapla = std::chrono::steady_clock::now();
  season.calculateWPRankingWithLaplace();
  auto time_end_Lapla = std::chrono::steady_clock::now();
  auto timeLapla = chrono::duration_cast<std::chrono::milliseconds>(time_end_Lapla - time_start_Lapla).count();

  archivo << n << "," << timeCMM << "," << timeWP << ","  << timeLapla << endl;



}

