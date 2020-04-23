#include <iostream>
#include <vector>

using namespace std;

#define matriz vector<vector<double>>
#define nat unsigned int

matriz elimGauss (matriz &M){
  matriz res = M;

  //for (int j = 0; j < res[0].size(); ++j) res[0][j] = res[0][j] / res[0][0]; // divido a la primer fila por la cte M[0][0]
                                                                              // (asi la primer celda vale 1)
  // todo:  queremos que la diagonal tenga unos? o con triangular alcanza?

  nat columna=0;
  nat fila=1;      //tengo que empezar a restar desde la 2da fila
  for (nat k = 0; k < res.size()-1; ++k) {  // fila pivot

    for (nat i = fila; i < res.size(); ++i) {  // fila actual en la que estoy restando
      double x = res[i][columna] / res[k][columna];              //cantidad de veces a restar esa fila

      for (nat j = columna; j < res[0].size(); ++j) {  //columna actual
        res[i][j] -= x * res[k][j];
      }
    }
    columna++;
    fila++;
  }
  return res;
}
