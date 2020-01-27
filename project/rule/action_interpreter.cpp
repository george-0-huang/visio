////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../error.h"
#include "../exception_handler.h"
#include <memory>
#include <string>
#include "action_interpreter.h"

using namespace visio;
using namespace errorreport;

namespace visio
{
    enum class MathExpression {
        Add,
        Sub,
        Assign
    };

    std::map<std::string, MathExpression> sMapMathExpression = {
        {"+", MathExpression::Add},
        {"-", MathExpression::Sub},
        {"=", MathExpression::Assign}
    };
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
ActionInterpreter::ActionInterpreter(
    std::shared_ptr<Product> product,
    const boost::property_tree::ptree& action_tree) :
    product_(product)
{
    auto object_node = action_tree.get_child("object");
    std::string object_value = object_node.get_value("");
    ThrowExceptionOnFalseWithReason((object_value.compare("product") == 0), Errors::kUserError, "Only support action on product");

    auto property_node = action_tree.get_child("property");
    std::string property_name = property_node.get_value("");

    auto operation_node = action_tree.get_child("operator");
    std::string operation_value = operation_node.get_value("");

    auto value_node = action_tree.get_child("value");
    std::string value_value = value_node.get_value("");

    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");
    std::string property_value;
    ThrowExceptionOnFalseWithReason(product_->GetAttribute(property_name, property_value),
        Errors::kInternal, "not supported product property");

    Operation(property_name, operation_value, property_value, value_value);
}

void ActionInterpreter::Operation(
    const std::string& property_name, 
    const std::string& operator_value, 
    const std::string& property_value, 
    const std::string& value_value)
{

    if (sMapMathExpression.find(operator_value) != sMapMathExpression.end())
    {
        switch (sMapMathExpression[operator_value])
        {
        case MathExpression::Add:
        {
            float value = Product::StringToFloat(property_value) + Product::StringToFloat(value_value);
            product_->SetAttribute(property_name, Product::FloatToString(value));
            action_report_ = operator_value + value_value;
            return;
        }
        case MathExpression::Sub:
        {
            float value = Product::StringToFloat(property_value);
            float change = Product::StringToFloat(value_value);
            if (value > change)
            {
                product_->SetAttribute(property_name, Product::FloatToString(value - change));
            }
            else
            {
                product_->SetAttribute(property_name, Product::FloatToString(0));
            }
            action_report_ = operator_value + value_value;
            return;
        }
        case MathExpression::Assign:
        {
            product_->SetAttribute(property_name, value_value);
            return;
        }
        }
    }

    ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "not supported action operator");    
}