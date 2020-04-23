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
  if (getline(file, line)) {
    auto s = split(line, ",");
    int cantPartidos = s.get(1), cantEquipos = s.get(0);
  }
  while(getline(file, line))

  vector<partido> partidos = new vector<partido>(cantPartidos);
  file.close();
}


