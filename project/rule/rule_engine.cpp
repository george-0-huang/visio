////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../error.h"
#include "../exception_handler.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "rule_engine.h"
#include "action_interpreter.h"
#include "condition_interpreter.h"

using namespace visio;
using namespace errorreport;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
ActionHistory::ActionHistory(std::shared_ptr<Product> product) : 
    product_(product)
{
    ThrowExceptionOnFalseWithReason(product_, Errors::kInternal, "product_ == nullptr");
    std::string rate;
    ThrowExceptionOnFalseWithReason(product->GetAttribute("rate", rate), Errors::kInternal,
        "rate property is missing");
  
    history_ += rate;
}

ActionHistory::~ActionHistory()
{
    std::cout << Report();
}

void ActionHistory::Record(std::string new_record)
{
    history_ += new_record;
}

std::string ActionHistory::Report()
{
    std::string rate;
    ThrowExceptionOnFalseWithReason(product_->GetAttribute("rate", rate), Errors::kInternal,
        "rate property is missing");

    return std::string("product.interest_rate == ") + rate + std::string(" (") + history_ + std::string(")\n");
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////
RuleEngine::RuleEngine(std::string name)
{
    input_stream_.exceptions(std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit);
    try {
        input_stream_.open(name.c_str());
        boost::property_tree::read_json(input_stream_, property_tree_);
    }
    catch (std::ifstream::failure& e) {
        std::string message(e.what());
        ThrowExceptionOnFalseWithReason(false, Errors::kUserError, 
            (message + std::string(". Fail to Open file: ") + name).c_str());
    }
}

RuleEngine::~RuleEngine()
{
    try {
        input_stream_.close();
    }
    catch (std::ifstream::failure& ) {
        // noop, not a good idea to throw from dtor
        // bad input_stream_ should have been caught already at open time
        // just add catch as a good defensive measure.
    }
}


void RuleEngine::ApplyRuleToProductAndPeron(std::shared_ptr<Product> product, std::shared_ptr<Person> person)
{
    try {
        ActionHistory history(product);
        for (auto& v : property_tree_.get_child("ruleList"))
        {
            auto node = v.second.get_child("ruleName");
            std::cout << node.get_value("") << std::endl;
            if (Condition(v.second.get_child("condition"), product, person))
            {
                history.Record(DoAction(v.second.get_child("action"), product));
            }
        }; 
    }
    catch (std::ifstream::failure& e) {
        ThrowExceptionOnFalseWithReason(input_stream_.eof(), Errors::kUserError, e.what());
    }
}

bool RuleEngine::Condition(
    const boost::property_tree::ptree& condtion_tree,
    std::shared_ptr<Product> product,
    std::shared_ptr<Person> person)
{
    ConditionInterpreter condition(condtion_tree, product, person);
    return condition.Value();
}

std::string RuleEngine::DoAction(
    const boost::property_tree::ptree& action_tree,
    std::shared_ptr<Product> product)
{  
    ActionInterpreter interpeter(product, action_tree);
    return  interpeter.Report();
}