include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)
FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)

add_executable(matrix_test ../src/Matrix.cpp ./matrix.cpp)

target_link_libraries(matrix_test
 PRIVATE
  GTest::GTest
)

add_test(matrix_tests matrix_test)

add_executable(activef_test ../src/ActivateFunction.cpp ./activatef.cpp)

target_link_libraries(activef_test
 PRIVATE
  GTest::GTest
)

add_test(activef_test activef_test)
