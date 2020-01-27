////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../error.h"
#include "../exception_handler.h"
#include <memory>
#include <string>
#include "value_interpreter.h"
#include "condition_interpreter.h"

using namespace visio;
using namespace errorreport;


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
    if (type_value.compare("condistion") == 0)
    {
        value_type_ = eValueType::eBoolean;
        auto sub_condition_node = value_tree.get_child("condition");
        ConditionInterpreter subCondition(sub_condition_node, product_, person_);
        value_ = (subCondition.Value() ? std::string("1") : std::string("0"));
    }
    else
    {
        if (type_value.compare("number") == 0)
        {
            value_type_ = eValueType::eNumber;
        }
        else if (type_value.compare("string") == 0)
        {
            value_type_ = eValueType::eNumber;
        }
        else
        {
            ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "unsupported value type");
        }
        auto property_node = value_tree.get_child("property");
        std::string property_name = property_node.get_value("");

        auto object_node = value_tree.get_child("object");
        std::string object_value = object_node.get_value("");

        auto default_node = value_tree.get_child("default");
        std::string default_value = default_node.get_value("");

        if (object_value.compare("none") == 0)
        {
            value_ = default_value;
        }
        else if (object_value.compare("person") == 0)
        {
            person_->GetAttribute(property_name, value_);
        }
        else if (object_value.compare("product") == 0)
        {
            product_->GetAttribute(property_name, value_);
        }
        else
        {
            ThrowExceptionOnFalseWithReason(false, Errors::kInternal, "unsupported object");
        }
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
