cmake_minimum_required(VERSION 3.2) 
# Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.

project(Network VERSION 1.0 LANGUAGES CXX)
#Название проекта

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(src)
add_subdirectory(tests)
