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
        Sub
    };

    std::map<std::string, MathExpression> sMapMathExpression = {
        {"+", MathExpression::Add},
        {"-", MathExpression::Sub}
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
    std::cout << object_value << std::endl;
    ThrowExceptionOnFalseWithReason((object_value.compare("product") == 0), Errors::kUserError, "Only support action on product");

    auto property_node = action_tree.get_child("property");
    std::string property_name = property_node.get_value("");
    std::cout << property_name << std::endl;

    auto operation_node = action_tree.get_child("operator");
    std::string operation_value = operation_node.get_value("");
    std::cout << operation_value << std::endl;

    auto value_node = action_tree.get_child("value");
    std::string value_value = value_node.get_value("");
    float change = Product::StringToFloat(value_value);

    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");

    std::string property_value;
    ThrowExceptionOnFalseWithReason(product_->GetAttribute(property_name, property_value),
        Errors::kInternal, "not supporte product property");

    Operation(property_name, operation_value, Product::StringToFloat(property_value), change);

    action_report_ = operation_value + value_value;
}

void ActionInterpreter::Operation(const std::string& property_name, const std::string& operator_value, float value, float change)
{
    switch (sMapMathExpression[operator_value])
    {
    case MathExpression::Add:
        product_->SetAttribute(property_name, Product::FloatToString(value + change));
        break;
    case MathExpression::Sub:
        if (value > change)
        {
            product_->SetAttribute(property_name, Product::FloatToString(value - change));
        }
        else
        {
            product_->SetAttribute(property_name, Product::FloatToString(0));
        }
        break;
    default:
        ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "not supported action operator");
    }
}