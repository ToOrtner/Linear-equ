#include <iostream>
#include <vector>

using namespace std;

#define matriz vector<vector<float>>

matriz elimGauss (matriz &M){
  matriz res = M;

  //for (int j = 0; j < res[0].size(); ++j) res[0][j] = res[0][j] / res[0][0]; // divido a la primer fila por la cte M[0][0]
                                                                              // (asi la primer celda vale 1)
  // todo:  queremos que la diagonal tenga unos? o con triangular alcanza?

  unsigned int columna=0;
  unsigned int fila=1;
  for (int k = 0; k < res.size()-1; ++k) {  // fila pivot

    for (int i = fila; i < res.size(); ++i) {  // fila actual
      float x = res[i][columna] / res[k][columna];              //cantidad de veces a restar esa fila

      for (int j = columna; j < res[0].size(); ++j) {  //columna actual
        res[i][j] -= x * res[k][j];
      }
    }
    columna++;
    fila++;
  }
  return res;
}
/*
int main() {
  matriz m = {{1, 2, 0}, {1, 3, 6}, {1, 7, 30}};

  matriz n = {{1, 2, 1}, {3, 2, 0}, {5, 2, 1}};
  matriz a = elimGauss(n);
  for (int i = 0; i < a.size(); ++i) {
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  " ;

    }
  }

  return 0;
}
*/