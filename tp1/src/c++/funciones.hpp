#ifndef FUNCIONES_HPP
#define FUNCIONES_HPP

#include <iostream>
#include <vector>
#include "defines.h"

void elimGaussExpandida(matrix &C, vector<ranking_t> &b);
void elimGauss(matrix &C);

void saveResult(string outputPath, vector<ranking_t> rankings);

void elimGauss(matrix &C){
  vector<ranking_t> b = vector<ranking_t>();
  elimGaussExpandida(C, b);
}

void elimGaussExpandida(matrix &C, vector<ranking_t> &b){

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

/**
 * Resuleve un sistema lineal dada C matriz y b la extension como vector.
 * @param C
 * @param b
 * @return
 */
vector<ranking_t> solveSystem(matrix &C, vector<ranking_t> &b) {
  //Aplico eliminacion gaussiana
  elimGaussExpandida(C, b);

  //Creo un vector de resultados
  vector<ranking_t> result = vector<ranking_t>(C.size(), 0);

  for (int fila = C.size() - 1; fila >= 0; --fila) {
    //Suma el elemento en la expansion de la matriz
    result[fila] += b[fila];
    //Resta todos los elementos de fila a la derecha de la diagonal
    for (int columna = C.size() - 1; columna > fila; --columna) {
      result[fila] -= C[fila][columna] * result[columna];
    }
    //Divide por el valor de la diagonal en esa fila.
    result[fila] = (double)(result[fila] / C[fila][fila]);
  }

  return result;
}

/**
 * Export ranking table in outputPath.
 * @param outputPath
 * @param rankings
 */
void saveResult(string outputPath, vector<ranking_t> rankings) {
  ofstream file(outputPath);
  file.precision(FILE_PRESITION);
  for (int i = 0; i < rankings.size(); ++i) {
    file << rankings[i] << endl;
  }
  file.close();
}


#endif // FUNCIONES_HPP