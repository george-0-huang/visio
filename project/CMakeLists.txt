# CMakeList.txt : CMake project for cards, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("project")
 
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME ON) 
#find_package(Boost REQUIRED COMPONENTS system) # header only libraries must not be added here

find_package(Boost 1.72.0)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})

  # Add unit test
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

  # Add product
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/product)
endif()

