cmake_minimum_required(VERSION 3.25)
project(CCA_Lista3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "/sample_data/vcpkg/installed/x64-linux/")

add_executable(CCA_Lista3 questao_6.cpp)
find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(CCA_Lista2 PRIVATE Matplot++::cimg Matplot++::matplot)
