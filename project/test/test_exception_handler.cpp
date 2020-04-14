/////////////////////////////////////////////////////////////////////////////////////////////////////////
//Autohor George Huang
//Revised 1/17/20020
//Copyright 2020
/////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "../exception_handler.h"
#include "../error.h"
#include <cstdint>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace errorreport;
using namespace testing;

class Exception_HandlerTestFixture :public ::testing::TestWithParam<int> {
};

INSTANTIATE_TEST_SUITE_P(
    Exception_Handler,
    Exception_HandlerTestFixture,
    ::testing::Values(
        Errors::kSuccess, Errors::kInternal, Errors::kUndefined
    ));

TEST_P(Exception_HandlerTestFixture, TEST_ThrowExceptionOnFalse)
{
    int code = GetParam();
    int line_number = 0;
    std::cout << "Test code: " << code << std::endl;
    EXPECT_THROW({
        try
        {   //All text within EXPECT_THROW({...} is cosnidered as one single line
            line_number = __LINE__; 
            ThrowExceptionOnFalse(false, code);
        }
        catch (const ErrorException & e)
        {
            // Verfiy the detailed_description
            EXPECT_THAT(e.what(), HasSubstr(std::string("Code ") + std::to_string(code)));
            EXPECT_THAT(e.what(), HasSubstr(__FILE__));
            EXPECT_THAT(e.what(), HasSubstr(std::string(", Line:") + std::to_string(line_number)));
            throw;
        }
    }, ErrorException);
}

TEST_P(Exception_HandlerTestFixture, TEST_ThrowExceptionOnFalseWithReason)
{
    int code = GetParam();
    std::string reason("Sorry, Oops");
    EXPECT_THROW({
        try
        {
            ThrowExceptionOnFalseWithReason(false, code, reason.c_str());
        }
        catch (const ErrorException & e)
        {
            // Veriy the reason
            EXPECT_THAT(e.what(), HasSubstr(reason));
            throw;
        }
        }, ErrorException);
}


TEST_P(Exception_HandlerTestFixture, TEST_ExceptionHandler)
{
    int code = GetParam();
    try
    {
        ThrowExceptionOnFalse(false, code);
    }
    catch (...)
    {
        // Veriy the retrun code of ExceptionHandler
        EXPECT_EQ(code, ErrorException::ExceptionHandler());
    }
}