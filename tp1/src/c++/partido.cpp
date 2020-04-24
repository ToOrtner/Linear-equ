//
// Created by awolfsdorf on 22/4/20.
//

#include "partido.h"

partido::partido(const string &fecha, const string &equipo1, int puntaje1, const string &equipo2, int puntaje2) : fecha(
        fecha), equipo1(equipo1), equipo2(equipo2), puntaje1(puntaje1), puntaje2(puntaje2) { }

const string &partido::getEquipo1() const {
  return equipo1;
}

void partido::setEquipo1(const string &equipo1) {
  partido::equipo1 = equipo1;
}

const string &partido::getEquipo2() const {
  return equipo2;
}

void partido::setEquipo2(const string &equipo2) {
  partido::equipo2 = equipo2;
}

int partido::getPuntaje1() const {
  return puntaje1;
}

void partido::setPuntaje1(int puntaje1) {
  partido::puntaje1 = puntaje1;
}

int partido::getPuntaje2() const {
  return puntaje2;
}

void partido::setPuntaje2(int puntaje2) {
  partido::puntaje2 = puntaje2;
}

string partido::getGanador() {
  return puntaje1 > puntaje2 ? equipo1 : equipo2;
}



const string &partido::getFecha() const {
  return fecha;
}

void partido::setFecha(const string &fecha) {
  partido::fecha = fecha;
}
