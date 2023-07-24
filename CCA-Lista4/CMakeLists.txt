cmake_minimum_required(VERSION 3.22)
project(CCA_Lista4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "~/clion-vcpkg/installed/x64-linux/")

add_executable(CCA_Lista4 questao_1.cpp)
find_package(Eigen3 REQUIRED)
find_package(Matplot++ CONFIG REQUIRED)
target_link_libraries(CCA_Lista4 PRIVATE Eigen3::Eigen Matplot++::cimg Matplot++::matplot)
