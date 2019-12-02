cmake_minimum_required(VERSION 2.6)
project(nearest_neighbor)

add_executable(nearest_neighbor
main.cpp
search.cpp
)

install(TARGETS nearest_neighbor RUNTIME DESTINATION bin)
