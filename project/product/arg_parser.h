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
#include <memory>
#include <string>
#include "product.h"

namespace visio
{
class ArgParser
{
public:

    ArgParser(int argc, char* argv[]);

    bool Success() {
        return parser_operation_done_;
    }

    std::shared_ptr<Person> GetPerson();
    std::shared_ptr<Product> GetProduct();
    std::string GetRuleFile();

private:
    bool IsNumber(const std::string& s);

private:
    bool parser_operation_done_;
    std::string product_name_;
    uint32_t score_;
    std::string state_;
    std::string rule_file_name_;
};
}