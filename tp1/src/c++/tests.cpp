#include "../../google-test/include/gtest/gtest.h"
#include "funciones.cpp"

TEST(funciones, prueba1){

  matriz n = {{1, 2, 1},
              {3, 2, 0},
              {5, 2, 1}};
  matriz a = elimGauss(n);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";

    }
  }
  matriz res = {{1, 2, 1},  // resultado que deberia dar
                {0, -4, -3},
                {0, 0, 2}};
  EXPECT_EQ(a, res);
}

TEST(funciones, prueba2){

  matriz m = {{1, 2, 0}, {1, 3, 6}, {1, 7, 30}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";

    }
  }
  matriz res = {{1, 2, 0},  // resultado que deberia dar
                {0, 1, 6},
                {0, 0, 0}};
  EXPECT_EQ(a, res);
}


TEST(funciones, pruebaNoCuadrada){

  matriz m = {{1, 2, 3, 4},
              {5, 6, 3, 2},
              {3, 2, 1, 5}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";

    }
  }
  matriz res = {{1, 2, 3, 4},  // resultado que deberia dar
                {0, -4, -12, -18},
                {0, 0, 4, 11}};
  EXPECT_EQ(a, res);
}

