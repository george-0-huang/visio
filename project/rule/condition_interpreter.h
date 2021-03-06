////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include "../product/product.h"
#include "../person/person.h"
#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>

namespace visio
{

class ValueInterpreter;
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class Name:  ConditionInterpreter
//Description: 
////////////////////////////////////////////////////////////////////////////////////////////////////////
class ConditionInterpreter
{
public:
    ConditionInterpreter(
        const boost::property_tree::ptree& condtion_tree,
        std::shared_ptr<Product> product,
        std::shared_ptr<Person> person);

    bool Value() { return value_; }

protected:
    void Operation(ValueInterpreter& value1, ValueInterpreter& value2, std::string& operation_value);
    std::shared_ptr<Product> product_;
    std::shared_ptr<Person> person_;
    bool value_;
};
}