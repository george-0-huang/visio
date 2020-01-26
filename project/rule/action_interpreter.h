////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include "../product/product.h"
#include <memory>
#include <string>
#include <boost/property_tree/ptree.hpp>


namespace visio
{
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class Name:  ActionInterpreter
//Description: 
////////////////////////////////////////////////////////////////////////////////////////////////////////
class ActionInterpreter
{
public:
    ActionInterpreter(
        std::shared_ptr<Product> product,
        const boost::property_tree::ptree& action_tree);

    std::string Report() { return action_report_; }
protected:
    void Operation(const std::string& property_name, const std::string& operator_value, float value, float change);
    std::shared_ptr<Product> product_;

    std::string action_report_;
};
}