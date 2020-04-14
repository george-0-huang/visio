# CMakeList.txt : CMake project for cards, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("project")
 
set(Boost_USE_STATIC_LIBS ON) 
set(Boost_USE_MULTITHREADED ON)  

find_package(Boost 1.72.0 REQUIRED COMPONENTS filesystem)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})

  # Add unit test
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)

  # Add product
  add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/product)

endif()


