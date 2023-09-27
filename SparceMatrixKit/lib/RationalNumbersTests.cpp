#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational_numberTestSuite, Rational_number_0)
{
    /**
     * Конструкторы, без переполнений
     */
    Rational_number<int64_t> a;
    Rational_number<int64_t> b(123);
    Rational_number<int64_t> c(312412, 1231234);
    Rational_number<int64_t> d("412321 / 432423 ");
    Rational_number<int64_t> e("123123", "-21412455");

    EXPECT_EQ(a.to_string(), "0/1");
    EXPECT_EQ(b.to_string(), "123/1");
    EXPECT_EQ(c.to_string(), "312412/1231234");
    EXPECT_EQ(d.to_string(), "412321/432423");
    EXPECT_EQ(e.to_string(), "-123123/21412455");
}

TEST(Rational_numberTestSuite, Rational_number_1)
{
    /**
     * Конструкторы, переполнения
     */

    EXPECT_THROW(Rational_number<int8_t> a(129), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int16_t> a(32768), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int32_t> a(-2147483649), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int64_t> a("-9223372036854775809"), RationalOverflowError<int64_t>);

    EXPECT_THROW(Rational_number<int8_t> a(1337, 1), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int16_t> a(2281337, 34), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int32_t> a(-22822813371337, 24), RationalOverflowError<int64_t>);
    EXPECT_THROW(Rational_number<int64_t> a("-9223372036854775809 / 123124"), RationalOverflowError<int64_t>);
}

TEST(Rational_numberTestSuite, Rational_number_2)
{
    /**
     * Операции + - / *
     */
    Rational_number<int64_t> first("213", "5");
    Rational_number<int64_t> second("-132", "44");
    EXPECT_EQ(first + second, Rational_number<int64_t>("8712", "220"));
    EXPECT_EQ(first - second, Rational_number<int64_t>("10032", "220"));
    EXPECT_EQ(first * second, Rational_number<int64_t>("-28116", "220"));
    EXPECT_EQ(first / second, Rational_number<int64_t>("-9372", "660"));

    /**
     * Выражение
     */
    auto res = 2 * ((2 + first) * second / 3 + 11 / (first - second));
    res.make_canonical();
    EXPECT_EQ(res.to_string(), "-50569/570");
}

TEST(Rational_numberTestSuite, Rational_number_3)
{
    /**
     * Операции += -= *= /=
     */
    Rational_number<int64_t> first("213", "5");
    Rational_number<int64_t> second("-132", "44");
    first += second;
    EXPECT_EQ(first, Rational_number<int64_t>("8712", "220"));
    first -= second;
    EXPECT_EQ(first, Rational_number<int64_t>("412368/9680"));
    first *= second;
    EXPECT_EQ(first, Rational_number<int64_t>("-54432576/425920"));
    first /= second;
    EXPECT_EQ(first, Rational_number<int64_t>("2395033344/56221440"));

    /**
     * Выражение
     */
    first += 2 + first++ / 5;
    first.make_canonical();
    EXPECT_EQ(first.to_string(), "1358/25");
}

TEST(Rational_numberTestSuite, Rational_number_4)
{
    /**
     * Операции ++, унарный -, получение нуля, make_canonical
     */
    Rational_number<int64_t> first("213", "5");
    Rational_number<int64_t> second("-132", "44");
    first += second;
    first.make_canonical();
    EXPECT_EQ(first, Rational_number<int64_t>("198", "5"));
    first++;
    EXPECT_EQ(first, Rational_number<int64_t>("203", "5"));
    first += 2;
    EXPECT_EQ(-first, Rational_number<int64_t>("-213", "5"));
    first -= Rational_number<int64_t>("213", "5");
    EXPECT_EQ(first, Rational_number<int64_t>("0/1"));
}

TEST(Rational_numberTestSuite, Rational_number_5)
{
    /**
     * Операции сравнения
     */
    Rational_number<int64_t> first(2);
    Rational_number<int64_t> second("4/2");

    EXPECT_EQ(first > second, false);
    EXPECT_EQ(first >= second, true);
    EXPECT_EQ(first < second, false);
    EXPECT_EQ(first <= second, true);
    EXPECT_EQ(first == second, true);
    EXPECT_EQ(first != second, false);

    EXPECT_EQ(first > 2, false);
    EXPECT_EQ(first >= 2, true);
    EXPECT_EQ(first < 2, false);
    EXPECT_EQ(first <= 2, true);
    EXPECT_EQ(first == 2, true);
    EXPECT_EQ(first != 2, false);

    EXPECT_EQ(2 > second, false);
    EXPECT_EQ(2 >= second, true);
    EXPECT_EQ(2 < second, false);
    EXPECT_EQ(2 <= second, true);
    EXPECT_EQ(2 == second, true);
    EXPECT_EQ(2 != second, false);
}

TEST(Rational_numberTestSuite, Rational_number_6)
{
    /**
     * Деление на 0
    */
    Rational_number<int64_t> first;
    Rational_number<int64_t> second("4/2");
    EXPECT_THROW(Rational_number<int8_t>("123/0"), RationalZeroDivisionError<int64_t>);
    EXPECT_THROW(second / first, RationalZeroDivisionError<int64_t>);
    EXPECT_THROW(first / first, RationalZeroDivisionError<int64_t>);
    EXPECT_THROW(second / first, RationalZeroDivisionError<int64_t>);
    EXPECT_THROW(5 / first, RationalZeroDivisionError<int64_t>);
    EXPECT_THROW(second / 0, RationalZeroDivisionError<int64_t>);
}
