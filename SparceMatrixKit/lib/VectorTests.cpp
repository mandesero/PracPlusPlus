#include "gtest/gtest.h"
#include "Rational.h"
#include "Vector.h"
#include "Matrix.h"

TEST(Vector_TestSuite, Vector_0)
{
    /**
     * Операции + - * /
     */
    Vector<Rational_number<int64_t>> v_1(2);
    v_1[1] = Rational_number<int64_t>("2/3");
    v_1[2] = Rational_number<int64_t>("5/6");

    Vector<Rational_number<int64_t>> v_2(2);
    v_2[1] = Rational_number<int64_t>("5/6");
    v_2[2] = Rational_number<int64_t>("3/4");

    EXPECT_EQ(
        (v_1 + v_2).to_string(),
        "27/18 38/24 ");
    EXPECT_EQ(
        (v_1 - v_2).to_string(),
        "-3/18 2/24 ");
    EXPECT_EQ(
        (v_1 * 3).to_string(),
        "6/3 15/6 ");
    EXPECT_EQ(
        (v_1 / Complex_number<>("1, 2")).to_string(),
        "0.000000+0.000000i 0.000000+0.000000i ");
}

TEST(Vector_TestSuite, Vector_1)
{
    /**
     * Унарный -, доступ к элементу по () и []
     */
    Vector<Rational_number<int64_t>> v_1(2);
    v_1[1] = Rational_number<int64_t>("2/3");
    v_1[2] = Rational_number<int64_t>("5/6");
    EXPECT_EQ(
        v_1[1], v_1(1));

    v_1[1] = Rational_number<int64_t>(5);
    EXPECT_EQ(
        v_1(1), Rational_number<int64_t>(5));
}

TEST(Vector_TestSuite, Vector_2)
{
    /**
     * Исключения
     */
    Vector<Rational_number<int64_t>> v_1(2);
    v_1[1] = Rational_number<int64_t>("2/3");
    v_1[2] = Rational_number<int64_t>("5/6");
    EXPECT_ANY_THROW(v_1 / Rational_number<int64_t>());
}
