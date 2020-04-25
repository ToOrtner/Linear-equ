#ifndef FUNCIONES_CPP
#define FUNCIONES_CPP

#include <iostream>
#include <vector>
#include "defines.h"

void elimGaussExpandida(matrix &C, vector<ranking_t> b);
void elimGauss(matrix &C);

void elimGauss(matrix &C){
    elimGaussExpandida(C, vector<ranking_t>());
}

void elimGaussExpandida(matrix &C, vector<ranking_t> b){

  bool isExpanded = !b.empty();

  nat columna=0;
  nat fila=1;      //tengo que empezar a restar desde la 2da fila

  //Primero triangulo
  for (nat fila_pivot = 0; fila_pivot < C.size() - 1; ++fila_pivot) {  // fila pivot

    for (nat fila_actual = fila; fila_actual < C.size(); ++fila_actual) {  // fila actual en la que estoy restando
      ranking_t multiplicador = C[fila_actual][columna] / C[fila_pivot][columna];              //cantidad de veces a restar esa fila


      for (nat columna_actual = columna; columna_actual < C[0].size(); ++columna_actual) {  //columna actual
        C[fila_actual][columna_actual] -= multiplicador * C[fila_pivot][columna_actual];
      }
      if (isExpanded)
        b[fila_actual] -= multiplicador * b[fila_pivot];
    }
    columna++;
    fila++;
  }
}

#endif // FUNCIONES_CPP