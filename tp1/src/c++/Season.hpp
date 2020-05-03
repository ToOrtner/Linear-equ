#ifndef TP1_SEASON_HPP
#define TP1_SEASON_HPP

#include <unordered_map>
#include "vector"
#include "defines.h"
#include "funciones.hpp"
#include <fstream>
#include "partido.h"
#include <set>

using namespace std;

class Season {
private:
  nat _cantPartidos;
  nat _cantEquipos;
  vector<partido> _partidos;

  set<int> _ordered_teams;

  // CMM variables
  matrix cmm_C;
  vector<ranking_t> cmm_b;

  vector<ranking_t> _calculateWPRanking(bool useLaplace);

public:
  Season(nat cantPartidos, nat cantEquipos, vector<partido> partidos, set<int> ordered_teams);
  unsigned int getCantEquipos() const;
  unsigned int getCantPartidos() const;
  void generateCMMStructures();
  void generateMatrix(bool useLaplace);
  vector<ranking_t> calculateCMMRanking();
  vector<ranking_t> calculateWPRanking();
  vector<ranking_t> calculateWPRankingWithLaplace();
  static Season parseDat(const string &path);
};

Season::Season(nat cantPartidos, nat cantEquipos, vector<partido> partidos, set<int> ordered_teams):
    _cantPartidos(cantPartidos), _cantEquipos(cantEquipos), _partidos(std::move(partidos)) {
  _ordered_teams = ordered_teams;
}

unsigned int Season::getCantEquipos() const {
  return _cantEquipos;
}

unsigned int Season::getCantPartidos() const {
  return _cantPartidos;
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

    //Acumulo la cantidad de partidos entre i y j, en C_ij y C_ji.
    int i = distance(_ordered_teams.begin(), _ordered_teams.find(stoi(team1)));
    int j = distance(_ordered_teams.begin(), _ordered_teams.find(stoi(team2)));
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
  return solveSystem(cmm_C, cmm_b);
}

vector<ranking_t> Season::calculateWPRanking() {
  return _calculateWPRanking(false);
}

vector<ranking_t> Season::calculateWPRankingWithLaplace() {
  return _calculateWPRanking(true);
}

vector<ranking_t> Season::_calculateWPRanking(bool useLaplace) {
  int defaultTotalValue = useLaplace ? 2 : 0;
  int defaultRankingValue = useLaplace ? 1 : 0;
  //Donde se guardan los partidos ganados
  vector<ranking_t> ranking = vector<ranking_t>(_cantEquipos, defaultRankingValue);
  vector<ranking_t> totalJugados = vector<ranking_t>(_cantEquipos, defaultTotalValue);

  nat count_team = 0;
  for (nat partido = 0; partido < _cantPartidos; partido++) {
    string team1 = _partidos[partido].getEquipo1();
    string team2 = _partidos[partido].getEquipo2();

    int i = distance(_ordered_teams.begin(), _ordered_teams.find(stoi(team1)));
    int j = distance(_ordered_teams.begin(), _ordered_teams.find(stoi(team2)));

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

/**
 * Read the file and generate array with all games
 * @param path
 * @return
 */
Season Season::parseDat(const string &path) {
  ifstream file (path);
  if (file.fail()) throw std::runtime_error("Archivo no encontrado");
  nat cantPartidos, cantEquipos;
  file >> cantEquipos >> cantPartidos;

  vector<partido> partidos = vector<partido>();
  string fecha, equipo1, equipo2;
  int p1, p2;
  nat i = 0;
  set<int> ordered_teams = set<int>();
  while(i < cantPartidos && file >> fecha >> equipo1 >> p1 >> equipo2 >> p2) {
    partido p(fecha, equipo1, p1, equipo2, p2);
    partidos.push_back(p);
    ordered_teams.insert(stoi(equipo1));
    ordered_teams.insert(stoi(equipo2));
    i++;
  }
  file.close();

  return Season(cantPartidos, cantEquipos, partidos, ordered_teams);
}

#endif //TP1_SEASON_HPP
