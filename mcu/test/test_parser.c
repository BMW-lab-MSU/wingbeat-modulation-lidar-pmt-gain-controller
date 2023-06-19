#include <unity.h>

#include "parser.h"

void setUp(void)
{

}

void tearDown(void)
{

}

void test_parser_not_enough_chars_4()
{
    const char *input[] = "t123\r";

    TEST_ASSERT_FALSE(validate_input(input));
}

void test_parser_not_enough_chars_3()
{
    const char *input[] = "s32\r";

    TEST_ASSERT_FALSE(validate_input(input));

}

void test_parser_not_enough_chars_2()
{
    const char *input[] = "a4\r";

    TEST_ASSERT_FALSE(validate_input(input));

}

void test_parser_not_enough_chars_1()
{
    const char *input[] = "2\r";

    TEST_ASSERT_FALSE(validate_input(input));

}

void test_parser_not_enough_chars_no_carriage_return()
{
    const char *input[] = "s2";

    TEST_ASSERT_FALSE(validate_input(input));
}

void test_parser_first_char_is_number()
{
    const char *input[] = "12345\r";

    TEST_ASSERT_FALSE(validate_input(input));
}

void test_parser_first_char_not_pmt_type()
{
    const char *input[] = "e0123\r";

    TEST_ASSERT_FALSE(validate_input(input));
}

void test_parser_valid_input_1()
{
    const char *input[] = "t0156\r";

    TEST_ASSERT_TRUE(validate_input(input));
}

void test_parser_valid_input_2()
{
    const char *input[] = "t1018\r";

    TEST_ASSERT_TRUE(validate_input(input));
}

void test_parser_valid_input_3()
{
    const char *input[] = "s0028\r";

    TEST_ASSERT_TRUE(validate_input(input));
}

void test_parser_valid_input_4()
{
    const char *input[] = "s1920\r";

    TEST_ASSERT_TRUE(validate_input(input));
}

void test_parser_valid_input_5()
{
    const char *input[] = "t0000\r";

    TEST_ASSERT_TRUE(validate_input(input));
}


void test_parser_invalid_upper_bound()
{
    const uint16_t voltage = 1023;
    const uint16_t upper_bound = 1000;
    const uint16_t lower_bound = 250;

    TEST_ASSERT_FALSE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_invalid_lower_bound()
{
    const uint16_t voltage = 023;
    const uint16_t upper_bound = 865;
    const uint16_t lower_bound = 250;

    TEST_ASSERT_FALSE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_valid_upper_bound_equal()
{
    const uint16_t voltage = 900;
    const uint16_t upper_bound = 900;
    const uint16_t lower_bound = 100;

    TEST_ASSERT_TRUE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_valid_upper_bound_less_than()
{
    const uint16_t voltage = 788;
    const uint16_t upper_bound = 1000;
    const uint16_t lower_bound = 100;

    TEST_ASSERT_TRUE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_valid_lower_bound_equal()
{
    const uint16_t voltage = 250;
    const uint16_t upper_bound = 1000;
    const uint16_t lower_bound = 250;

    TEST_ASSERT_TRUE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_valid_lower_bound_greater_than()
{
    const uint16_t voltage = 251;
    const uint16_t upper_bound = 1000;
    const uint16_t lower_bound = 250;

    TEST_ASSERT_TRUE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_invalid_bounds_1()
{
    const uint16_t voltage = 300;
    const uint16_t upper_bound = 200;
    const uint16_t lower_bound = 250;

    TEST_ASSERT_FALSE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}

void test_parser_invalid_bounds_2()
{
    const uint16_t voltage = 300;
    const uint16_t upper_bound = 200;
    const uint16_t lower_bound = 400;

    TEST_ASSERT_FALSE(validate_voltage_bounds(voltage, upper_bound, lower_bound));
}


int main(int argc, char **argv)
{
    UNITY_BEGIN();

    RUN_TEST(test_parser_not_enough_chars_1);
    RUN_TEST(test_parser_not_enough_chars_2);
    RUN_TEST(test_parser_not_enough_chars_3);
    RUN_TEST(test_parser_not_enough_chars_4);
    RUN_TEST(test_parser_not_enough_chars_no_carriage_return);
    RUN_TEST(test_parser_first_char_is_number);
    RUN_TEST(test_parser_first_char_not_pmt_type);

    RUN_TEST(test_parser_valid_input_1);
    RUN_TEST(test_parser_valid_input_2);
    RUN_TEST(test_parser_valid_input_3);
    RUN_TEST(test_parser_valid_input_4);
    RUN_TEST(test_parser_valid_input_5);

    RUN_TEST(test_parser_invalid_bounds_1);
    RUN_TEST(test_parser_invalid_bounds_2);
    RUN_TEST(test_parser_invalid_lower_bound);
    RUN_TEST(test_parser_invalid_upper_bound);
    RUN_TEST(test_parser_valid_lower_bound_equal);
    RUN_TEST(test_parser_valid_lower_bound_greater_than);
    RUN_TEST(test_parser_valid_upper_bound_equal);
    RUN_TEST(test_parser_valid_upper_bound_less_than);

    UNITY_END();
}