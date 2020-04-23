#include "../../google-test/include/gtest/gtest.h"
#include "funciones.cpp"

TEST(funciones, prueba1){

  matriz n = {{1, 2, 1},
              {3, 2, 0},
              {5, 2, 1}};
  matriz a = elimGauss(n);

  for (int i = 0; i < a.size(); ++i) {
    cout << endl;
    for (int j = 0; j < a[0].size(); ++j) {
      cout << a[i][j] << "  ";

    }
  }
  matriz res = {{1, 2, 1},
                {0, -4, -3},
                {0, 0, 2}};
  EXPECT_EQ(a, res);
}