cmake_minimum_required(VERSION 3.23)
project(MagicContainers)

set(CMAKE_CXX_STANDARD 20)

add_executable(MagicContainers sources/MagicalContainer.cpp sources/MagicalContainer.hpp Demo.cpp Test.cpp TestCounter.cpp sources/magicalLinkedList.cpp sources/magicalLinkedList.hpp)
