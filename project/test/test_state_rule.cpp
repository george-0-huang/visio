#include "../rule/rule_engine.h"
#include "../person/person.h"
#include "../product/product.h"
#include "../exception_handler.h"
#include "../error.h"
#include <cstdint>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace visio;
using namespace errorreport;
using namespace testing;

namespace teststaterule
{
    struct TestParam
    {
        uint32_t person_score;
        std::string person_state;
        std::string product_name;
    };

    class StateRuleTestFixture :public TestWithParam<TestParam>
    {
    protected:
        float default_rate_ = 5.0;
    };


    std::vector<TestParam> params{
        {0, "texas", "30FIX"},
        {362, "florida", "30FIX"},
        {719, "texas", "30FIX"},
        {720, "texas", "30FIX"},
        {721, "florida", "30FIX"},
    };

    INSTANTIATE_TEST_CASE_P(
        StateRuleTest,
        StateRuleTestFixture,
        ValuesIn(params)
    );

    TEST_P(StateRuleTestFixture, TEST_state)
    {
        uint32_t score = GetParam().person_score;
        std::string state = GetParam().person_state;
        std::string product_name = GetParam().product_name;

        RuleEngine engine("rule_spec/rules_state.txt");
        std::shared_ptr<Person> person = std::shared_ptr<Person>(new Person(score, state));
        std::shared_ptr<Product> product = std::shared_ptr<Product>(new Product(product_name));

        EXPECT_NO_THROW(engine.ApplyRuleToProductAndPerson(product, person));

        std::string result_rate;
        EXPECT_NO_THROW(product->GetAttribute("rate", result_rate));
        EXPECT_EQ(stof(result_rate), default_rate_);

        std::string result_disqualified;
        EXPECT_NO_THROW(product->GetAttribute("disqualified", result_disqualified));
        EXPECT_EQ(stof(result_disqualified), (state.compare("florida") == 0? 1 : 0));
    }
}
