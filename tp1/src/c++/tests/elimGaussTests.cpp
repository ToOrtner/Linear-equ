#include "include/gtest/gtest.h"
#include "../defines.h"
#include "expecteds.h"
#include "../funciones.cpp"

TEST(funciones, prueba1) {

  matrix m = {{1, 2, 1},
              {3, 2, 0},
              {5, 2, 1}};
  elimGauss(m);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << m[i][j] << "  ";
    }
  }
  matrix res = {{1, 2, 1}, // resultado que deberia dar
                {0, -4, -3},
                {0, 0, 2}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, res, precision);
}

TEST(funciones, prueba2) {

  matrix m = {{1, 2, 0},
              {1, 3, 6},
              {1, 7, 30}};

  elimGauss(m);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << m[i][j] << "  ";
    }
  }
  matrix res = {{1, 2, 0}, // resultado que deberia dar
                {0, 1, 6},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, res, precision);
}

TEST(funciones, pruebaNoCuadrada) {

  matrix m = {{1, 2, 3, 4}, {5, 6, 3, 2}, {3, 2, 1, 5}};

  elimGauss(m);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << m[i][j] << "  ";
    }
  }
  matrix res = {{1, 2, 3, 4}, // resultado que deberia dar
                {0, -4, -12, -18},
                {0, 0, 4, 11}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, res, precision);
}

TEST(funciones, pruebaNoCuadrada2) {

  matrix m = {{5, 1, 3}, {2, 1, 3}, {4, 2, 3}, {2, 3, 2}};

  elimGauss(m);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << m[i][j] << "  ";
    }
  }
  matrix res = {{5, 1, 3}, // resultado que deberia dar
                {0, 3.0 / 5.0, 9.0 / 5.0},
                {0, 0, -3},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, res, precision);
}

TEST(funciones, decYneg) {

  matrix m = {
      {-1.5, 1.2, 2.2},
      {5.1, -12.2, 1.1},
      {-2.2, 31.1, 1.2},
      {0.2, -5.1, 5.1}};

  elimGauss(m);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << fixed << setprecision(9) << m[i][j] << "  ";
    }
    cout << endl;
  }
  matrix res = {{-1.5, 1.2, 2.2}, // resultado que deberia dar
                {0, -203.0 / 25, 429.0 / 50},
                {0, 0, 352921.0 / 12180.0},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, res, precision);
}

TEST(funciones, prueba1Exp) {

  matrix m = {{1, 2, 1},
              {3, 2, 0},
              {5, 2, 1}};
  vector<ranking_t> b = {1,2,3};
  elimGaussExpandida(m, b);

  for (nat i = 0; i < m.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (nat j = 0; j < m[0].size(); ++j) {
      cout << m[i][j] << "  ";
    }
  }
  matrix resM = {{1, 2, 1}, // resultado que deberia dar
                {0, -4, -3},
                {0, 0, 2}};
  vector<ranking_t> resB = {1, -1, 0};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(m, resM, precision);
  EXPECT_VECTOR_FLOATS_NEARLY_EQ(b, resB, precision);
}
