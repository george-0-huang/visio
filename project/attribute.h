////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "../error.h"
#include "../exception_handler.h"
#include <map>
#include <string>


namespace visio
{
////////////////////////////////////////////////////////////////////////////////////////////////////////
//Class Name:  Attribute
//Description: Base class for any class that need attributes member
//             A clone memthod could be added to directly poluplate the attributes from SQL query  
////////////////////////////////////////////////////////////////////////////////////////////////////////
class Attribute
{
public:

    virtual ~Attribute() { }

    bool GetAttribute(const std::string& attribute_name, std::string& value)
    {
        std::map<std::string, std::string>::iterator it = value_map_.end();
        if (value_map_.find(attribute_name) != it)
        {
            value = value_map_[attribute_name];
            return true;
        }

        return false;
    }

    bool SetAttribute(const std::string& attribute_name, std::string& value)
    {
        std::map<std::string, std::string>::iterator it = value_map_.end();
        if (value_map_.find(attribute_name) != it)
        {
            value_map_[attribute_name] = value;
            return true;
        }
        return false;
    }

protected:
    std::map<std::string, std::string> value_map_;
};
}