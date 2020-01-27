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

class ValueInterpreter
{
public:
    enum class eValueType
    {
        eNumber,
        eString,
        eBoolean   //boolean value will be represented as [std::string("0"), std::string("1")]
    };

    ValueInterpreter(
        const boost::property_tree::ptree& value_tree,
        std::shared_ptr<Product> product,
        std::shared_ptr<Person> person);

    std::string Value() { return value_; }

    bool BoolValueHelper();
    float NumberValueHelper();

protected:
    void Operation(const std::string& property_name, const std::string& operator_value, float value, float change);
    std::shared_ptr<Product> product_;
    std::shared_ptr<Person> person_;

    std::string value_;
    eValueType value_type_;
};

}