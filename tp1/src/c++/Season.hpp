#ifndef TP1_SEASON_HPP
#define TP1_SEASON_HPP

#include <unordered_map>
#include "vector"
#include "defines.h"
#include "funciones.hpp"

using namespace std;

class Season {
private:
  nat _cantPartidos;
  nat _cantEquipos;
  vector<partido> _partidos;

  unordered_map<string, int> teams_ref;

  // CMM variables
  matrix cmm_C;
  vector<ranking_t> cmm_b;

public:
  Season(nat cantPartidos, nat cantEquipos, vector<partido> partidos);
  unsigned int getCantEquipos() const;
  void generateCMMStructures();
  void generateMatrix(bool useLaplace);
  vector<ranking_t> calculateCMMRanking();
  vector<ranking_t> calculateWPRanking();

};

Season::Season(nat cantPartidos, nat cantEquipos, vector<partido> partidos):
    _cantPartidos(cantPartidos), _cantEquipos(cantEquipos), _partidos(std::move(partidos)) { }

unsigned int Season::getCantEquipos() const {
  return _cantEquipos;
}

void Season::generateMatrix(bool useLaplace) {
  int b_default = useLaplace ? 1 : 0;
  //Armo matriz cantEquipos x cantEquipos
  cmm_C = matrix(_cantEquipos, vector<ranking_t>(_cantEquipos, 0));
  cmm_b = vector<ranking_t>(_cantEquipos, b_default);
  nat count_team = 0;
  for (nat partido = 0; partido < _cantPartidos; partido++) {
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
    cmm_C[i][j]--;
    cmm_C[j][i]--;

    /*
     * Calculo el score de cada equipo en cmm_b
     * cmm_b = 1 + (w_i - l_i)/2  => cmm_b = 1 + w_i/2 - l_i/2
     */
    if(_partidos[partido].getGanador() == team1) {
      cmm_b[i] += 0.5;
      cmm_b[j] -= 0.5;
    } else {
      cmm_b[i] -= 0.5;
      cmm_b[j] += 0.5;
    }
    //Completo la diagonal
    cmm_C[i][i]++;
    cmm_C[j][j]++;
  }

  //Sumo 2 en la diagonal
  if (useLaplace) {
    for (nat i = 0; i < _cantEquipos; i++) {
      cmm_C[i][i] += 2;
    }
  }
}

void Season::generateCMMStructures() {
  generateMatrix(true);
}

vector<ranking_t> Season::calculateCMMRanking() {
  generateCMMStructures();
  return  solveSystem(cmm_C, cmm_b);
}

vector<ranking_t> Season::calculateWPRanking() {
  //Donde se guardan los partidos ganados
  vector<ranking_t> ranking = vector<ranking_t>(_cantEquipos, 0);
  vector<ranking_t> totalJugados = vector<ranking_t>(_cantEquipos, 0);

  nat count_team = 0;
  for (nat partido = 0; partido < _cantPartidos; partido++) {
    string team1 = _partidos[partido].getEquipo1();
    string team2 = _partidos[partido].getEquipo2();

    //Si el team no esta definido, defino y mapeo con un indice fila de la matriz.
    if (teams_ref.find(team1) == teams_ref.end()) {
      teams_ref[team1] = count_team;
      count_team++;
    }
    if (teams_ref.find(team2) == teams_ref.end()) {
      teams_ref[team2] = count_team;
      count_team++;
    }

    int i = teams_ref[team1];
    int j = teams_ref[team2];
    //Acumulo los partidos jugados
    totalJugados[i]++;
    totalJugados[j]++;

    //Acumulo las victorias del ganador
    if(_partidos[partido].getGanador() == team1) {
      ranking[i]++;
    } else {
      ranking[j]++;
    }
  }

  //Calculo el score como ganados/total jugados en partidosGanados.
  for (int k = 0; k < _cantEquipos; ++k) {
    ranking[k] = (double)(ranking[k] / totalJugados[k]);
  }

  return ranking;
}

#endif //TP1_SEASON_HPP
