#include <iostream>
#include <vector>
#include "partido.h"
#include <fstream>

using namespace std;

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

int main() {
  std::cout << "Hello, World!" << std::endl;
  return 0;
}

vector<partido> parseDat(string path) {
  ifstream file (path);
  string line;
  int cantPartidos, cantEquipos;
  if (getline(file, line)) {
    vector<string> s = split(line, " ");
    cantPartidos = stoi(s[1]);
    cantEquipos = stoi(s[0]);
  }

  vector<partido> partidos = vector<partido>(cantPartidos);
  while(getline(file, line)) {
    vector<string> s = split(line, " ");
    partido p(s[0], s[1], stoi(s[2]), s[3], stoi(s[4]));
    partidos.push_back(p);
  }
  file.close();
  return partidos;
}


