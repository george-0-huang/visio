////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/17/20020
//Copyright 2020
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace errorreport
{   //Avoid C++11 strongly typed enum class to allow implict convertion to int type return in main()
    enum Errors {
        kSuccess = 0, 
        kInternal = -1,
        kUserError = -2,
        //........
        kUndefined = -512
    }; 
}
   