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
    const std::string& property_name,
    const std::string& operator_value,
    float change) :
    product_(product)
{
    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");

    std::string property_value;
    ThrowExceptionOnFalseWithReason(product_->GetAttribute(property_name, property_value),
        Errors::kInternal, "not supporte product property");

    Operation(property_name, operator_value, Product::StringToFloat(property_value), change);
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