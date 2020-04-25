#ifndef TP1_EXPECTEDS_H
#define TP1_EXPECTEDS_H

#include "include/gtest/gtest.h"

#define EXPECT_VECTOR_FLOATS_NEARLY_EQ(expected, actual, precision) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idy = 0; idy < std::min(expected.size(), actual.size()); ++idy) \
        { \
            EXPECT_NEAR(expected[idy], actual[idy], precision) << "at index: " << idy; \
        }

#define EXPECT_MATRIX_FLOATS_NEARLY_EQ(expected, actual, precision) \
        EXPECT_EQ(expected.size(), actual.size()) << "Array sizes differ.";\
        for (size_t idx = 0; idx < expected.size(); ++idx) \
        { \
          EXPECT_VECTOR_FLOATS_NEARLY_EQ(expected[idx], actual[idx], precision) \
        }


#endif //TP1_EXPECTEDS_H
