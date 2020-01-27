////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../error.h"
#include "../exception_handler.h"
#include <memory>
#include <string>
#include "condition_interpreter.h"
#include "value_interpreter.h"

using namespace visio;
using namespace errorreport;

namespace visio
{
    enum class CompExpression {
        EQ,
        LT,
        GT,
        LE,
        GE,
        NE
    };

    std::map<std::string, CompExpression> sMapCompExpression = {
        {"EQ", CompExpression::EQ},
        {"LT", CompExpression::LT},
        {"GT", CompExpression::GT},
        {"LE", CompExpression::LE},
        {"GE", CompExpression::GE},
        {"NE", CompExpression::NE}
    };


    enum class StringCompExpression {
        MATCH,
        CONTAIN,
    };

    std::map<std::string, StringCompExpression> sMapStringCompExpression = {
        {"MATCH", StringCompExpression::MATCH},
        {"CONTAIN", StringCompExpression::CONTAIN}
    };

    enum class LogicalExpression {
        AND,
        OR
    };

    std::map<std::string, LogicalExpression> sMapLogicalExpression = {
        {"AND", LogicalExpression::AND},
        {"OR", LogicalExpression::OR}
    };
}


ConditionInterpreter::ConditionInterpreter(
    const boost::property_tree::ptree& condtion_tree,
    std::shared_ptr<Product> product,
    std::shared_ptr<Person> person) :
    product_(product),
    person_(person),
    value_(false)
{
    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");
    ThrowExceptionOnFalseWithReason(person_, Errors::kInternal, "product_ == nullptr");

    auto value1_node = condtion_tree.get_child("value1");

    std::string property_name = value1_node.get_value("");

    auto operation_node = condtion_tree.get_child("operator");
    std::string operation_value = operation_node.get_value("");

    auto value2_node = condtion_tree.get_child("value2");
    std::string property_name2 = value2_node.get_value("");

    ValueInterpreter value1_interpreter(value1_node, product, person);
    ValueInterpreter value2_interpreter(value2_node, product, person);

    Operation(value1_interpreter, value2_interpreter, operation_value);
}

void ConditionInterpreter::Operation(ValueInterpreter& value1, ValueInterpreter& value2, std::string& operation_value)
{
    if (sMapCompExpression.find(operation_value) != sMapCompExpression.end())
    {
        switch (sMapCompExpression[operation_value])
        {
        case CompExpression::EQ:
            value_ = (value1.NumberValueHelper() == value2.NumberValueHelper());
            return;
        case CompExpression::LT:
            value_ = (value1.NumberValueHelper() < value2.NumberValueHelper());
            return;
        case CompExpression::GT:
            value_ = (value1.NumberValueHelper() > value2.NumberValueHelper());
            return;
        case CompExpression::LE:
            value_ = (value1.NumberValueHelper() <= value2.NumberValueHelper());
            return;
        case CompExpression::GE:
            value_ = (value1.NumberValueHelper() >= value2.NumberValueHelper());
            return;
        case CompExpression::NE:
            value_ = (value1.NumberValueHelper() != value2.NumberValueHelper());
            return;
        };
    }
 
    if (sMapStringCompExpression.find(operation_value) != sMapStringCompExpression.end())
    {
        switch (sMapStringCompExpression[operation_value])
        {
        case StringCompExpression::MATCH:
            value_ = (value2.Value().compare(value1.Value()) == 0);
            return;
        case StringCompExpression::CONTAIN:
            value_ = (value2.Value().find(value1.Value()) != std::string::npos);
            return;
        };
    }

    if (sMapLogicalExpression.find(operation_value) != sMapLogicalExpression.end())
    {
        switch (sMapLogicalExpression[operation_value])
        {
        case LogicalExpression::AND:
            value_ = (value1.BoolValueHelper() && value2.BoolValueHelper());
            return;
        case LogicalExpression::OR:
            value_ = (value1.BoolValueHelper() || value2.BoolValueHelper());
            return;
        }
    }
    ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "not supported condition operator");
}