# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("test")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()


# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")  
endif()
include_directories("${gmock_SOURCE_DIR}/include") 

add_definitions(-D _ENABLE_ATOMIC_ALIGNMENT_FIX)

# Now simply link against gtest or gtest_main as needed.
add_executable(test 
    ../exception_handler.h
    ../exception_handler.cpp
    ../attribute.h
    ../exception_handler.h
    ../exception_handler.cpp
    ../rule/rule_engine.h
    ../rule/rule_engine.cpp
    ../rule/action_interpreter.h
    ../rule/action_interpreter.cpp
    ../rule/condition_interpreter.h
    ../rule/condition_interpreter.cpp
    ../rule/value_interpreter.h
    ../rule/value_interpreter.cpp
    ../person/person.h
    test_score_rule.cpp
    test_state_rule.cpp
    test_product_name_rule.cpp
    test_exception_handler.cpp
    )
target_include_directories(test PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(test gtest_main ${Boost_LIBRARIES})
add_test(NAME unit_test COMMAND test)

