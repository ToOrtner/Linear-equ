#include "include/gtest/gtest.h"
#include "../src/c++/funciones.hpp"
#include "expecteds.h"

TEST(solve, resolverSistema) {

  matrix m = {{1, 2, 1},
              {3, 2, 0},
              {5, 2, 1}};
  vector<ranking_t> b = {1,2,3};

  vector<ranking_t> result = solveSystem(m, b);

  for (int i = 0; i < result.size(); ++i) {
    cout << "x" + to_string(i + 1) + ": " << result[i] << endl;
  }

  vector<ranking_t> resEsperado = {0.5, 0.25, 0};

  EXPECT_VECTOR_FLOATS_NEARLY_EQ(result, resEsperado, precision);
}


TEST(solve, resolverSistema2) {

  matrix m = {{1, 2, 1, 2},
              {3, 2, 0, 3},
              {2, 2, 1, 1},
              {1, 3, 4, 2}};
  vector<ranking_t> b = {2, 1,-2,3};

  vector<ranking_t> result = solveSystem(m, b);

  for (int i = 0; i < result.size(); ++i) {
    cout << "x" + to_string(i + 1) + ": " << result[i] << endl;
  }

  vector<ranking_t> resEsperado = {-17./12., -5./4., 3./4., 31./12.};

  EXPECT_VECTOR_FLOATS_NEARLY_EQ(result, resEsperado, precision);
}

