#include "../../google-test/include/gtest/gtest.h"
#include "funciones.cpp"
#include "defines.h"

#define EXPECT_MATRIX_FLOATS_NEARLY_EQ(expected, actual, thresh) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < std::min(expected.size(), actual.size()); ++idx) \
        { \
            for (size_t idy = 0; idy < std::min(expected[0].size(), actual[0].size()); ++idy) \
            { \
                EXPECT_NEAR(expected[idx][idy], actual[idx][idy], thresh) << "at index: " << idx << "," << idy;\
            }}



TEST(funciones, prueba1) {

  matriz n = {{1, 2, 1}, {3, 2, 0}, {5, 2, 1}};
  matriz a = elimGauss(n);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";
    }
  }
  matriz res = {{1, 2, 1}, // resultado que deberia dar
                {0, -4, -3},
                {0, 0, 2}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(a, res, precision);
}

TEST(funciones, prueba2) {

  matriz m = {{1, 2, 0}, {1, 3, 6}, {1, 7, 30}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";
    }
  }
  matriz res = {{1, 2, 0}, // resultado que deberia dar
                {0, 1, 6},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(a, res, precision);
}

TEST(funciones, pruebaNoCuadrada) {

  matriz m = {{1, 2, 3, 4}, {5, 6, 3, 2}, {3, 2, 1, 5}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";
    }
  }
  matriz res = {{1, 2, 3, 4}, // resultado que deberia dar
                {0, -4, -12, -18},
                {0, 0, 4, 11}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(a, res, precision);
}

TEST(funciones, pruebaNoCuadrada2) {

  matriz m = {{5, 1, 3}, {2, 1, 3}, {4, 2, 3}, {2, 3, 2}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";
    }
  }
  matriz res = {{5, 1, 3}, // resultado que deberia dar
                {0, 3.0 / 5.0, 9.0 / 5.0},
                {0, 0, -3},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(a, res, precision);
}

TEST(funciones, decYneg) {

  matriz m = {
      {-1.5, 1.2, 2.2}, {5.1, -12.2, 1.1}, {-2.2, 31.1, 1.2}, {0.2, -5.1, 5.1}};

  matriz a = elimGauss(m);

  for (int i = 0; i < a.size(); ++i) { // imprimo lo que da la funcion
    for (int j = 0; j < a[0].size(); ++j) {
      cout << fixed << setprecision(9) << a[i][j] << "  ";
    }
    cout << endl;
  }
  matriz res = {{-1.5, 1.2, 2.2}, // resultado que deberia dar
                {0, -203.0 / 25, 429.0 / 50},
                {0, 0, 352921.0 / 12180.0},
                {0, 0, 0}};
  EXPECT_MATRIX_FLOATS_NEARLY_EQ(a, res, precision);
}
