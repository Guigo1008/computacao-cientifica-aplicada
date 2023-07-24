cmake_minimum_required(VERSION 3.22)
project(CCA_Lista3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_PREFIX_PATH "~/clion-vcpkg/installed/x64-linux/")

add_executable(CCA_Lista3 questao_3.cpp)
find_package(Matplot++ CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
target_link_libraries(CCA_Lista3 PRIVATE Matplot++::cimg Matplot++::matplot nlohmann_json::nlohmann_json)
