#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
#include "../src/ActivateFunction.h"

TEST(ActivateFunctionTest, CatchInitError) {
	ActivateFunction actFunc;
	double v[5] = {1, 2, 3, 4, 5};

  try {
		actFunc.use(v, 5);
    FAIL();  // exception not thrown as expected
  } catch (std::runtime_error err) {
      EXPECT_STREQ("Error:actFuncInit", err.what());
  }
}


TEST(ActivateFunctionTest, ReLU) {
	ActivateFunction F;
	F.actFunc = ReLU;
	double v[5] = {-1, 0, 0.5, 1, 2};
	F.use(v, 5);
	ASSERT_THAT(v, testing::ElementsAre(-0.01, 0, 0.5, 1, 1.01));
}


int main(int argc, char *argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

