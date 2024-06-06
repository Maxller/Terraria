cmake_minimum_required(VERSION 3.10)
project(TierraAria)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)

# Incluir directorios
include_directories(include)

# Encontrar la librería SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Añadir el ejecutable
add_executable(TerrariaLikeWorld src/main.cpp)

# Enlazar SFML a tu ejecutable
target_link_libraries(TerrariaLikeWorld sfml-graphics sfml-window sfml-system)
