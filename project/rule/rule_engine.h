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
#include <fstream>
#include <boost/property_tree/ptree.hpp>

namespace visio
{
class ActionHistory
{
public:
    explicit ActionHistory(std::shared_ptr<Product> product);
    ~ActionHistory();

    void Record(std::string new_record);

    std::string Report();
private:
    std::string history_;
    std::shared_ptr<Product> product_;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class Name:  RuleEngine
//Description: 
////////////////////////////////////////////////////////////////////////////////////////////////////////
class RuleEngine
{
public:
    explicit RuleEngine(std::string name);
    ~RuleEngine();

    void ApplyRuleToProductAndPeron(std::shared_ptr<Product> product, std::shared_ptr<Person> person);
protected:
    bool Condition(
        const boost::property_tree::ptree& condition_tree,
        std::shared_ptr<Product> product,
        std::shared_ptr<Person> person);
    std::string DoAction(
        const boost::property_tree::ptree& action_tree,
        std::shared_ptr<Product> product);

private:
    RuleEngine(RuleEngine&) = delete;
    RuleEngine& operator=(RuleEngine) = delete;

    std::ifstream input_stream_;
    boost::property_tree::ptree property_tree_;
};
}