# CMakeList.txt : CMake project for test, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("product")


add_executable(product
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
    main.cpp
    arg_parser.h
    arg_parser.cpp
    product.h
    )

target_include_directories(product PUBLIC ${Boost_INCLUDE_DIRS})
 
