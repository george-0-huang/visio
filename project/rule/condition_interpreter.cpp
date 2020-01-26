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

    enum class LogicalExpression {
        AND,
        OR
    };

    std::map<std::string, LogicalExpression> sMapLogicalExpression = {
        {"AND", LogicalExpression::AND},
        {"OR", LogicalExpression::OR}
    };
}

ValueInterpreter::ValueInterpreter(
    const boost::property_tree::ptree& value_tree,
    std::shared_ptr<Product> product,
    std::shared_ptr<Person> person) :
    product_(product),
    person_(person)
{
    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");
    ThrowExceptionOnFalseWithReason(person_, Errors::kInternal, "product_ == nullptr");

    auto type_node = value_tree.get_child("type");
    std::string type_value = type_node.get_value("");
    if (type_value.compare("regular") == 0)
    {
        auto property_node = value_tree.get_child("property");
        std::string property_name = property_node.get_value("");
        std::cout << property_name << std::endl;

        auto object_node = value_tree.get_child("object");
        std::string object_value = object_node.get_value("");
        std::cout << object_value << std::endl;

        auto default_node = value_tree.get_child("default");
        std::string default_value = default_node.get_value("");
        std::cout << default_value << std::endl;

        value_type_ = eValueType::eNumber;
        if (object_value.compare("none") == 0)
        {
            value_ = default_value;
        }
        else if (object_value.compare("person") == 0)
        {
            person_->GetAttribute(property_name, value_);
        }
        else if (object_value.compare("prodcut") == 0)
        {
            product_->GetAttribute(property_name, value_);
        }
        else
        {
            ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "unsupported object");
        }
    }
    else
    {
        value_type_ = eValueType::eBoolean;
        auto sub_condition_node = value_tree.get_child("condition");
        ConditionInterpreter subCondition(sub_condition_node, product_, person_);
        value_ = (subCondition.Value() ? std::string("1") : std::string("0"));
    }
}


bool ValueInterpreter::BoolValueHelper()
{
    ThrowExceptionOnFalseWithReason(value_type_ == eValueType::eBoolean, Errors::kInternal, "unsupported type");
    return(value_.compare("0") != 0);
}

float ValueInterpreter::NumberValueHelper()
{
    ThrowExceptionOnFalseWithReason(value_type_ == eValueType::eNumber, Errors::kInternal, "unsupported type");
    return(stof(value_));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
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
    std::cout << property_name << std::endl;

    auto operation_node = condtion_tree.get_child("operator");
    std::string operation_value = operation_node.get_value("");
    std::cout << operation_value << std::endl;

    auto value2_node = condtion_tree.get_child("value2");
    std::string property_name2 = value2_node.get_value("");
    std::cout << property_name2 << std::endl;

    ValueInterpreter value1_interpreter(value1_node, product, person);
    ValueInterpreter value2_interpreter(value2_node, product, person);

    Operation(value1_interpreter, value2_interpreter, operation_value);
}

void ConditionInterpreter::Operation(ValueInterpreter& value1, ValueInterpreter& value2, std::string& operation_value)
{
    switch (sMapCompExpression[operation_value])
    {
    case CompExpression::EQ:
        value_ = (value1.NumberValueHelper() == value2.NumberValueHelper());
        break;
    case CompExpression::LT:
        value_ = (value1.NumberValueHelper() < value2.NumberValueHelper());
        break;
    case CompExpression::GT:
        value_ = (value1.NumberValueHelper() > value2.NumberValueHelper());
        break;
    case CompExpression::LE:
        value_ = (value1.NumberValueHelper() <= value2.NumberValueHelper());
        break;
    case CompExpression::GE:
        value_ = (value1.NumberValueHelper() >= value2.NumberValueHelper());
        break;
    case CompExpression::NE:
        value_ = (value1.NumberValueHelper() != value2.NumberValueHelper());
        break;
    default:
        switch (sMapLogicalExpression[operation_value])
        {
        case LogicalExpression::AND:
            value_ = (value1.BoolValueHelper() && value2.BoolValueHelper());
            break;
        case LogicalExpression::OR:
            value_ = (value1.BoolValueHelper() || value2.BoolValueHelper());
            break;
        default:
            ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "not supported condition operator");
        }
    }
}