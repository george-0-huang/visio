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

namespace testscorerule
{
    struct TestParam
    {
        uint32_t person_score;
        std::string person_state;
        std::string product_name;
    };

    class ScoreRuleTestFixture :public TestWithParam<TestParam>
    {
    protected:
        float default_rate_ = 5.0;
    };


    std::vector<TestParam> params{
        {0, "texas", "30FIX"},
        {362, "texas", "30FIX"},
        {719, "texas", "30FIX"},
        {720, "texas", "30FIX"},
        {721, "texas", "30FIX"},
    };

    INSTANTIATE_TEST_CASE_P(
        ScoreRuleTest,
        ScoreRuleTestFixture,
        ValuesIn(params)
    );

    TEST_P(ScoreRuleTestFixture, TEST_score)
    {
        uint32_t score = GetParam().person_score;
        std::string state = GetParam().person_state;
        std::string product_name = GetParam().product_name;

        RuleEngine engine("rule_spec/rules_score.txt");
        std::shared_ptr<Person> person = std::shared_ptr<Person>(new Person(score, state));
        std::shared_ptr<Product> product = std::shared_ptr<Product>(new Product(product_name));

        EXPECT_NO_THROW(engine.ApplyRuleToProductAndPerson(product, person));

        std::string result_rate;
        EXPECT_NO_THROW(product->GetAttribute("rate", result_rate));

        float expect_result_rate = default_rate_;
        if (score > 720) expect_result_rate -= float(0.3);
        if (score < 720) expect_result_rate += float(0.5);
        EXPECT_EQ(stof(result_rate), expect_result_rate);

        std::string result_disqualified;
        EXPECT_NO_THROW(product->GetAttribute("disqualified", result_disqualified));
        EXPECT_EQ(stof(result_disqualified), 0);
    }
}
