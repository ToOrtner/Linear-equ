#include <iostream>
#include <vector>
#include "partido.h"
#include <fstream>

using namespace std;
vector<partido> parseDat(string path);

vector<string> split(const string& str, const string& delim)
{
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  do
  {
    pos = str.find(delim, prev);
    if (pos == string::npos) pos = str.length();
    string token = str.substr(prev, pos-prev);
    if (!token.empty()) tokens.push_back(token);
    prev = pos + delim.length();
  }
  while (pos < str.length() && prev < str.length());
  return tokens;
}

int main(int argc, char* argv[]) {
  std::cout << "Hello, World!" << std::endl;
  int method = stoi(argv[1]);
  string inputPath = argv[2];
  string outputPath = argv[3];
  parseDat(inputPath);
  return 0;
}

vector<partido> parseDat(string path) {
  ifstream file (path);
  int cantPartidos, cantEquipos;
  file >> cantEquipos >> cantPartidos;

  vector<partido> partidos = vector<partido>(cantPartidos);
  string fecha, equipo1, equipo2;
  int p1, p2;
  int i = 0;
  while(i < cantPartidos && file >> fecha >> equipo1 >> p1 >> equipo2 >> p2) {
    partido p(fecha, equipo1, p1, equipo2, p2);
    partidos[i] = p;
    i++;
  }
  file.close();
  return partidos;
}


