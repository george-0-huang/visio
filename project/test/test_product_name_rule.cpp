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

namespace testproductnamerule
{
    struct TestParam
    {
        uint32_t person_score;
        std::string person_state;
        std::string product_name;
    };

    class ProductNameTestFixture :public TestWithParam<TestParam>
    {
    protected:
        float default_rate_ = 5.0;
    };


    std::vector<TestParam> params{
        {0, "texas", "7-1 ARM"},
        {362, "florida", "30FIX"},
        {719, "texas", "7-1 ARM"},
        {720, "texas", "30FIX"},
        {721, "florida", "7-1 ARM"},
    };

    INSTANTIATE_TEST_CASE_P(
        ProductNameTest,
        ProductNameTestFixture,
        ValuesIn(params)
    );

    TEST_P(ProductNameTestFixture, TEST_product_name)
    {
        uint32_t score = GetParam().person_score;
        std::string state = GetParam().person_state;
        std::string product_name = GetParam().product_name;

        RuleEngine engine("rule_spec/rules_product_name.txt");
        std::shared_ptr<Person> person = std::shared_ptr<Person>(new Person(score, state));
        std::shared_ptr<Product> product = std::shared_ptr<Product>(new Product(product_name));

        EXPECT_NO_THROW(engine.ApplyRuleToProductAndPerson(product, person));

        std::string result_rate;
        EXPECT_NO_THROW(product->GetAttribute("rate", result_rate));

        float expect_result_rate = default_rate_;
        if (product_name.compare("7-1 ARM") == 0 ) expect_result_rate += 0.5;
        EXPECT_EQ(stof(result_rate), expect_result_rate);
    }
}

