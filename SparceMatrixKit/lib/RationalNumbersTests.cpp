#include "gtest/gtest.h"
#include "Rational.h"

TEST(Rational_numberTestSuite, Rational_number_0)
{
    /**
     * Конструкторы
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
     * Операции + - / *
     */
    Rational_number<int64_t> first("213", "5");
    Rational_number<int64_t> second("-132", "44");
    EXPECT_EQ(first + second, Rational_number<int64_t>("8712", "220"));
    EXPECT_EQ(first - second, Rational_number<int64_t>("10032", "220"));
    EXPECT_EQ(first * second, Rational_number<int64_t>("-28116", "220"));
    EXPECT_EQ(first / second, Rational_number<int64_t>("-9372", "660"));
}

TEST(Rational_numberTestSuite, Rational_number_2)
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
}

TEST(Rational_numberTestSuite, Rational_number_3)
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

TEST(Rational_numberTestSuite, Rational_number_4)
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
}

TEST(Rational_numberTestSuite, Rational_number_5)
{
    /**
     * Деление на 0
    */
    Rational_number<int64_t> first;
    Rational_number<int64_t> second("4/2");
    EXPECT_ANY_THROW(second / first);
}
