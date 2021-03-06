////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include "../attribute.h"
#include <map>
#include <string>
#include <sstream>      // std::ostringstream


namespace visio
{
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class Name:  Product
//Description: 
////////////////////////////////////////////////////////////////////////////////////////////////////////
class Product : public Attribute
{
    
public:
    Product(const std::string& name)
    {        
        static float kDefaultRate = 5.0;
        value_map_.insert({ "name", name });
        value_map_.insert({ "rate", FloatToString(kDefaultRate) });
        value_map_.insert({ "disqualified", std::string("0") });
    }

    static std::string FloatToString(float number)
    {
        std::ostringstream ss;
        ss << number;
        return std::string(ss.str());
    }

    static float StringToFloat(const std::string& str)
    {
        return std::stof(str);
    }

};
}