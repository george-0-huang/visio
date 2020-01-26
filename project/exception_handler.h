////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/17/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include <exception>
#include <string>
#include <iostream>
#include "error.h"

namespace errorreport
{
class ErrorException : public virtual std::exception
{
public:

    ErrorException(int code, const char* file, int line, const char* reason = nullptr) :
        code_(code),
        detail_description_(std::string("Code ") + std::to_string(code) +
            std::string("\nFile:") + (file != nullptr ? std::string(file) : std::string("Unknown")) +
            std::string(", Line:") + std::to_string(line) +
            (reason != nullptr ? std::string("\n") + std::string(reason) + std::string("\n") : std::string("\n"))
        )
    {
    };

    const char* what() const throw ()
    {
        return detail_description_.c_str();
    }

    int report() const
    {
        std::cout << this->what();
        return code_;
    }

    static int ExceptionHandler();
private:
    ErrorException& operator=(const ErrorException&) = delete;
protected:
    const int code_;
    const std::string detail_description_;
};

//The macro will be placed in calling code during preprocessor to reflect the caller's __FILE__/__LINE__
#define ThrowExceptionOnFalseWithReason(condition, code, reason) if(!(condition)) throw ErrorException(code, __FILE__, __LINE__, reason);

#define ThrowExceptionOnFalse(condition, code) ThrowExceptionOnFalseWithReason(condition, code, nullptr)

}