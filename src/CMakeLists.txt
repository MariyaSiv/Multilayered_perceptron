add_compile_options(
    -Wall
    -Wextra
) # Опции компилятора

add_executable(Project ./Utils.cpp ./Matrix.cpp ./Network.cpp ./Reader.cpp ./main.cpp)

