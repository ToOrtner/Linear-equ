#ifndef TP1_SEASON_HPP
#define TP1_SEASON_HPP

#include "vector"
#include <map>
#include "defines.h"

using namespace std;

class Season {
private:
  int _cantPartidos;
  int _cantEquipos;
  vector<partido> _partidos;

  map<string, int> teams_ref;
  matrix C;

public:
  Season();

  Season(int cantPartidos, int cantEquipos, vector<partido> partidos);

};

Season::Season() {}

Season::Season(int cantPartidos, int cantEquipos, vector<partido> partidos):
      _cantPartidos(cantPartidos), _cantEquipos(cantEquipos), _partidos(std::move(partidos)) {

  //Armo matriz cantEquipos x cantEquipos
  C = matrix(cantEquipos, vector<ranking_t>(cantEquipos));

  int team = 0;
  for (int i = 0; i < cantPartidos; i++) {
    string team1 = _partidos[i].getEquipo1();
    string team2 = _partidos[i].getEquipo2();
    cout << get<0>(_partidos[i].getGanador()) << endl;
  }

}


#endif //TP1_SEASON_HPP
