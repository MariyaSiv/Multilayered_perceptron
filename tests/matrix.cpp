#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../src/Matrix.h"

TEST(MatrixTest, MatrixIsInitWith0) {
	Matrix m; int n = 3;
	m.Init(n, n);
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			EXPECT_EQ(0, m(i, j));
		}
	}
}

TEST(MatrixTest, CatchMultiError) {
	Matrix m; m.Init(3, 3);
	double v[4] = {1, 2, 3, 4};
	double out[4];
	int n = 4;
  try {
		Matrix::Multi(m, v, n, out);
    FAIL();  // exception not thrown as expected
  } catch (std::runtime_error err) {
      EXPECT_STREQ("Error:Multi", err.what());
  }
}

TEST(MatrixTest, Multi) {
	int n = 3;
	Matrix m; m.Init(n, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			m(i, j) = i+j;
		}
	}
	
	double v[3] = {1., 2., 3.};
	double out[3];
	int k = 3;

	Matrix::Multi(m, v, n, out);
	ASSERT_THAT(out, testing::ElementsAre(8, 14, 20));
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
