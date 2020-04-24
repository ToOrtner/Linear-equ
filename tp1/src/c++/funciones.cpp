#ifndef FUNCIONES_CPP
#define FUNCIONES_CPP

#include <iostream>
#include <vector>

using namespace std;

#define dato long double
#define matriz vector<vector<dato>>
#define nat unsigned int

matriz elimGauss (matriz &M){
  matriz res = M;

  nat columna=0;
  nat fila=1;      //tengo que empezar a restar desde la 2da fila
  for (nat k = 0; k < res.size()-1; ++k) {  // fila pivot

    for (nat i = fila; i < res.size(); ++i) {  // fila actual en la que estoy restando
      dato x = res[i][columna] / res[k][columna];              //cantidad de veces a restar esa fila

      for (nat j = columna; j < res[0].size(); ++j) {  //columna actual
        res[i][j] -= x * res[k][j];
      }
    }
    columna++;
    fila++;
  }
  return res;
}

#endif // FUNCIONES_CPP