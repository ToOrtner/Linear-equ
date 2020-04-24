#ifndef TP1_SEASON_HPP
#define TP1_SEASON_HPP

#include "vector"
#include <unordered_map>
#include "defines.h"

using namespace std;

class Season {
private:
  int _cantPartidos;
  int _cantEquipos;
  vector<partido> _partidos;

  unordered_map<string, int> teams_ref;
  matrix C;
  vector<ranking_t> b;

public:
  Season();

  Season(int cantPartidos, int cantEquipos, vector<partido> partidos);

};

Season::Season() {}

Season::Season(int cantPartidos, int cantEquipos, vector<partido> partidos):
      _cantPartidos(cantPartidos), _cantEquipos(cantEquipos), _partidos(std::move(partidos)) {

  //Armo matriz cantEquipos x cantEquipos
  C = matrix(cantEquipos, vector<ranking_t>(cantEquipos, 0));
  b = vector<ranking_t>(cantEquipos, 1);
  int count_team = 0;
  for (int partido = 0; partido < cantPartidos; partido++) {
    string team1 = _partidos[partido].getEquipo1();
    string team2 = _partidos[partido].getEquipo2();

    //Si el team no esta definido, defino y mapeo con un indice fila de la matriz.
    if(teams_ref.find(team1) == teams_ref.end()) {
      teams_ref[team1] = count_team;
      count_team++;
    }
    if(teams_ref.find(team2) == teams_ref.end()) {
      teams_ref[team2] = count_team;
      count_team++;
    }

    //Acumulo la cantidad de partidos entre i y j, en C_ij y C_ji.
    int i = teams_ref[team1];
    int j = teams_ref[team2];
    C[i][j]--;
    C[j][i]--;

    /*
     * Calculo el score de cada equipo en b
     * b = 1 + (w_i - l_i)/2  => b = 1 + w_i/2 - l_i/2
     */
    if(_partidos[partido].getGanador() == team1) {
      b[i] += 0.5;
      b[j] -= 0.5;
    } else {
      b[i] -= 0.5;
      b[j] += 0.5;
    }
    //Completo la diagonal
    C[i][i]++;
    C[j][j]++;
  }

  //Sumo 2 en la diagonal
  for (int i = 0; i < cantEquipos; i++) {
    C[i][i] += 2;
  }

}


#endif //TP1_SEASON_HPP
