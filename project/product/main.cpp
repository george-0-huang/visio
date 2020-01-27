////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "..\error.h"
#include "..\exception_handler.h"
#include "..\person\person.h"
#include "..\rule\rule_engine.h"
#include <iostream>
#include "arg_parser.h"
#include "product.h"

using namespace errorreport;
using namespace visio;


int main(int argc, char* argv[])
{
    try
    {
        ArgParser params(argc, argv);
        if(!params.Success()) return Errors::kSuccess;

        RuleEngine engine(params.GetRuleFile());

        engine.ApplyRuleToProductAndPerson(params.GetProduct(), params.GetPerson());

        return Errors::kSuccess;
    }
    catch (...)
    {
        return ErrorException::ExceptionHandler();
    }
}

