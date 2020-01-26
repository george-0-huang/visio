////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include "../person/person.h"
#include <cstdint>
#include <string>
#include <limits.h>
#include "arg_parser.h"
#include "product.h"

using namespace visio;
using namespace errorreport;

ArgParser::ArgParser(int argc, char* argv[]) : parser_operation_done_(false)
{
    if ((argc == 5) && IsNumber(argv[2]))
    {
        product_name_ = std::string(argv[1]);
        score_ = atoi(argv[2]);
        state_ = std::string(argv[3]);
        rule_file_name_ = std::string(argv[4]);
        std::cout << "Build Product "<< product_name_ << " for the person (Socre : " 
            << score_ << ", state : " << state_ << " )" << std::endl;

        parser_operation_done_ = true;
    }
    else
    {
        std::cout << "Command: product [ProductName] [Score] [State] [RuleFileName]" << std::endl;
    }
}


std::shared_ptr<Person> ArgParser::GetPerson()
{
    ThrowExceptionOnFalseWithReason(Success(), Errors::kInternal, "ArgParser failed its parsing operation");
    return std::shared_ptr<Person>(new Person(score_,  state_));
}


std::shared_ptr<Product> ArgParser::GetProduct()
{
    ThrowExceptionOnFalseWithReason(Success(), Errors::kInternal, "ArgParser failed its parsing operation");
    return std::shared_ptr<Product>(new Product(product_name_));
}

std::string ArgParser::GetRuleFile()
{ 
    ThrowExceptionOnFalseWithReason(Success(), Errors::kInternal, "ArgParser failed its parsing operation");
    return rule_file_name_;
};

bool ArgParser::IsNumber(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

