#include "gtest/gtest.h"
#include "Rational.h"

TEST(Complex_numberTestSuite, Complex_number_0)
{
    /**
     * Конструкторы
     */
    Complex_number<> a_1(1, 2);
    Complex_number<int> a_2(3, 4);
    Complex_number<double, int64_t> a_3(3, 2);

    Complex_number<int> b_1;
    Complex_number<int> b_2(12);
    Complex_number<int> b_3("-1", "3");
    Complex_number<int> b_4("123,412");

    EXPECT_EQ(a_1.to_string(), "1.000000+2.000000i");
    EXPECT_EQ(a_2.to_string(), "3+4i");
    EXPECT_EQ(a_3.to_string(), "3.000000+2i");

    EXPECT_EQ(b_1.to_string(), "0+0i");
    EXPECT_EQ(b_2.to_string(), "12+0i");
    EXPECT_EQ(b_3.to_string(), "-1+3i");
    EXPECT_EQ(b_4.to_string(), "123+412i");
}

TEST(Complex_numberTestSuite, Complex_number_1)
{
    /**
     * Операции + - / *
     */
    Complex_number<int> first("-1", "3");
    Complex_number<int> second("123,412");

    EXPECT_EQ(first + second, Complex_number<int>(122, 415));
    EXPECT_EQ(first - second, Complex_number<int>(-124, -409));
    EXPECT_EQ(first * second, Complex_number<int>(-1359, -43));
    EXPECT_EQ(first / second, Complex_number<int>(111, -78));
}

TEST(Complex_numberTestSuite, Complex_number_2)
{
    /**
     * Операции += -= *= /=
     */
    Complex_number<int> first("-1", "3");
    Complex_number<int> second("123,412");

    first += second;
    EXPECT_EQ(first, Complex_number<int>(122, 415));
    first -= second;
    EXPECT_EQ(first, Complex_number<int>(-1, 3));
    first *= second;
    EXPECT_EQ(first, Complex_number<int>(-1359, -559539));
    first /= second;
    EXPECT_EQ(first, Complex_number<int>(0, 0));
}

TEST(Complex_numberTestSuite, Complex_number_3)
{
    /**
     * Операции ++, унарный -
     */
    Complex_number<int> first("-1", "3");
    Complex_number<int> second("123,412");
    first++;
    EXPECT_EQ(first, Complex_number<int>(0, 3));
    first += 2;
    EXPECT_EQ(-first, Complex_number<int>(-2, -3));
}

TEST(Complex_numberTestSuite, Complex_number_4)
{
    /**
     * Операции сравнения
     */
    Complex_number<int> first(15, -12);
    Complex_number<int> second(8, -17);

    EXPECT_EQ(first > second, true);
    EXPECT_EQ(first >= second, true);
    EXPECT_EQ(first < second, false);
    EXPECT_EQ(first <= second, false);
    EXPECT_EQ(first == second, false);
    EXPECT_EQ(first != second, true);
}

TEST(Complex_numberTestSuite, Complex_number_5)
{
    /**
     * Деление на 0
    */
    Complex_number<int> first;
    Complex_number<int> second(8, -17);
    EXPECT_ANY_THROW(second / first);
}
