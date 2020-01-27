////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/25/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <exception>
#include <string>
#include <iostream>
#include "error.h"
#include "exception_handler.h"

using namespace errorreport;

    int ErrorException::ExceptionHandler()
    {
        try
        {
            throw;
        }
        catch (const ErrorException & e)
        {
            return e.report();
        }
        catch (const std::exception & e)
        {
            std::cout << e.what() << std::endl;
        }
        catch (...)
        {
            std::cout << "Unknonw Exception" << std::endl;
        }

        return Errors::kInternal;
    }
