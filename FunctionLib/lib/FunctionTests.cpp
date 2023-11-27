#include "gtest/gtest.h"
#include <iostream>
#include <math.h>

#include "Factory.h"

class Function_test : public testing::Test
{
};
FunctionFactory F;

TEST(Function_test, EmptyIdent)
{
    auto i1 = F.Create("ident");
    auto i2 = F.Create("ident", 0);
    auto i3 = F.Create("ident", {0});
    Identical i4;
    ASSERT_EQ(typeid(*i1), typeid(*i2));
    ASSERT_EQ(typeid(*i2), typeid(*i3));
    ASSERT_EQ(typeid(*i3), typeid(i4));
}

TEST(Function_test, EmptyConst)
{
    auto c1 = F.Create("const");
    auto c2 = F.Create("const", 0);
    auto c3 = F.Create("const", {0});
    Constant c4;
    ASSERT_EQ(typeid(*c1), typeid(*c2));
    ASSERT_EQ(typeid(*c2), typeid(*c3));
    ASSERT_EQ(typeid(*c3), typeid(c4));
}

TEST(Function_test, EmptyPower)
{
    auto p1 = F.Create("power");
    auto p2 = F.Create("power", 0);
    auto p3 = F.Create("power", {0});
    Power p4;
    ASSERT_EQ(typeid(*p1), typeid(*p2));
    ASSERT_EQ(typeid(*p2), typeid(*p3));
    ASSERT_EQ(typeid(*p3), typeid(p4));
}

TEST(Function_test, EmptyExp)
{
    auto e1 = F.Create("exp");
    auto e2 = F.Create("exp", 0);
    auto e3 = F.Create("exp", {0});
    Exponent e4;
    ASSERT_EQ(typeid(*e1), typeid(*e2));
    ASSERT_EQ(typeid(*e2), typeid(*e3));
    ASSERT_EQ(typeid(*e3), typeid(e4));
}

TEST(Function_test, EmptyPoly)
{
    auto pol1 = F.Create("polynomial");
    auto pol2 = F.Create("polynomial", 0);
    auto pol3 = F.Create("polynomial", {0});
    Polynom pol4;
    ASSERT_EQ(typeid(*pol1), typeid(*pol2));
    ASSERT_EQ(typeid(*pol2), typeid(*pol3));
    ASSERT_EQ(typeid(*pol3), typeid(pol4));
}

TEST(Function_test, EmptyToString)
{
    auto i1 = F.Create("ident");
    ASSERT_EQ(i1->ToString(), std::to_string((double)0));

    auto c1 = F.Create("const");
    ASSERT_EQ(c1->ToString(), std::to_string((double)0));

    auto p1 = F.Create("power");
    ASSERT_EQ(p1->ToString(), std::to_string((double)1));

    auto e1 = F.Create("exp");
    ASSERT_EQ(e1->ToString(), std::to_string((double)1));

    auto pol1 = F.Create("polynomial");
    ASSERT_EQ(pol1->ToString(), std::to_string((double)0));
}

TEST(Function_test, ToString)
{
    ASSERT_EQ(F.Create("ident", 4)->ToString(), std::to_string((double)4) + "x");
    ASSERT_EQ(F.Create("ident", {1, 2, 3})->ToString(), std::to_string((double)1) + "x");

    ASSERT_EQ(F.Create("const", -5)->ToString(), std::to_string((double)-5));
    ASSERT_EQ(F.Create("const", {2, 3})->ToString(), std::to_string((double)2));

    ASSERT_EQ(F.Create("power", 3)->ToString(), std::to_string((double)1) + "x^3");
    ASSERT_EQ(F.Create("power", {1, 5})->ToString(), std::to_string((double)1) + "x");

    ASSERT_EQ(F.Create("exp", 4)->ToString(), "exp(" + std::to_string((double)4) + "x)");
    ASSERT_EQ(F.Create("exp", {-3, 5})->ToString(), "exp(" + std::to_string((double)-3) + "x)");

    ASSERT_EQ(F.Create("polynomial", 4)->ToString(), std::to_string((double)4));
    ASSERT_EQ(F.Create("polynomial", {-1, 0, 2})->ToString(), std::to_string((double)-1) + " + " + std::to_string((double)2) + "x^2");
}

TEST(FunctionTest, IdentFunction)
{
    auto i1 = F.Create("ident", 3);
    auto i2 = F.Create("ident", {-2, 5});
    ASSERT_FLOAT_EQ((*i1)(10), 30.0);
    ASSERT_FLOAT_EQ((*i2)(20), -40.0);
}

TEST(FunctionTest, ConstFunction)
{
    auto c1 = F.Create("const", -4);
    auto c2 = F.Create("const", {1.6, 5});
    ASSERT_EQ((*c1)(-100), -4.0);
    ASSERT_EQ((*c2)(100), 1.6);
}

TEST(FunctionTest, PowerFunction)
{
    auto p1 = F.Create("power", -1);
    auto p2 = F.Create("power", {1, -1});
    ASSERT_FLOAT_EQ((*p1)(100), 0.01);
    ASSERT_FLOAT_EQ((*p2)(10), 10.0);
}

TEST(FunctionTest, ExpFunction)
{
    auto e1 = F.Create("exp", 4);
    auto e2 = F.Create("exp", {1, 5});
    ASSERT_FLOAT_EQ((*e1)(10), exp(40.0));
    ASSERT_FLOAT_EQ((*e2)(10), exp(10.0));
}

TEST(FunctionTest, PolynomialFunction)
{
    auto pol1 = F.Create("polynomial", {0, -2});
    auto pol2 = F.Create("polynomial", {1, -2, 3, -4});
    ASSERT_FLOAT_EQ((*pol1)(-5), 10.0);
    ASSERT_FLOAT_EQ((*pol2)(1.6), -10.904);
}

TEST(Function_test, DerivIdent)
{
    auto i1 = F.Create("ident", -1.223);
    auto i2 = F.Create("ident", {1, 0, 0, 1});
    ASSERT_FLOAT_EQ(i1->GetDeriv(10), -1.223);
    ASSERT_FLOAT_EQ(i2->GetDeriv(10), 1.0);
}

TEST(Function_test, DerivConst)
{
    auto c1 = F.Create("const", 4123);
    auto c2 = F.Create("const", {-1432, 5123});
    ASSERT_FLOAT_EQ(c1->GetDeriv(10), 0.0);
    ASSERT_FLOAT_EQ(c2->GetDeriv(10), 0.0);
}

TEST(Function_test, DerivPower)
{
    auto p1 = F.Create("power", -5);
    auto p2 = F.Create("power", {6, 5});
    ASSERT_FLOAT_EQ(p1->GetDeriv(100), 0);
    ASSERT_FLOAT_EQ(p2->GetDeriv(10), 600000);
}

TEST(Function_test, DerivExp)
{
    auto e1 = F.Create("exp", -3);
    auto e2 = F.Create("exp", {-1, 5});
    ASSERT_FLOAT_EQ(e1->GetDeriv(-10), -3 * exp(30.0));
    ASSERT_FLOAT_EQ(e2->GetDeriv(10), -exp(-10.0));
}

TEST(Function_test, DerivPolynomial)
{
    auto pol1 = F.Create("polynomial", {0, 1, 5});
    auto pol2 = F.Create("polynomial", {1, 2, 3, 4});
    ASSERT_FLOAT_EQ(pol1->GetDeriv(10), 101.0);
    ASSERT_FLOAT_EQ(pol2->GetDeriv(10), (*F.Create("polynomial", {2, 6, 12, 0}))(10));
}

TEST(Function_test, OperationsPolynomial)
{
    auto pol1 = F.Create("polynomial", {1, -2, 0, 3});
    auto pol2 = F.Create("polynomial", {0, -2, -3, 3});

    auto pol_sum = F.Create("polynomial", {1, -4, -3, 6});
    auto pol_dif = F.Create("polynomial", {1, 0, 3, 0});
    auto pol_mul = F.Create("polynomial", {0, -2, 1, 9, -12, -9, 9});

    ASSERT_FLOAT_EQ((*pol1 + *pol2)(10), (*pol_sum)(10));
    ASSERT_FLOAT_EQ((*pol1 - *pol2)(10), (*pol_dif)(10));
    ASSERT_FLOAT_EQ((*pol1 * *pol2)(10), (*pol_mul)(10));
    ASSERT_FLOAT_EQ((*pol1 / *pol2)(10), 1.1123134);
}

TEST(Function_test, OperationsThrows)
{
    auto i1 = F.Create("ident", -1);
    ASSERT_THROW(*i1 + "123", std::logic_error);
    ASSERT_THROW(*i1 - "123", std::logic_error);
    ASSERT_THROW(*i1 * "123", std::logic_error);
    ASSERT_THROW(*i1 / "123", std::logic_error);
    ASSERT_THROW(*i1 + 123, std::logic_error);
    ASSERT_THROW(*i1 - 123, std::logic_error);
    ASSERT_THROW(*i1 * 123, std::logic_error);
    ASSERT_THROW(*i1 / 123, std::logic_error);

    auto c1 = F.Create("const", 4123);
    ASSERT_THROW(*c1 + "123", std::logic_error);
    ASSERT_THROW(*c1 - "123", std::logic_error);
    ASSERT_THROW(*c1 * "123", std::logic_error);
    ASSERT_THROW(*c1 / "123", std::logic_error);
    ASSERT_THROW(*c1 + 123, std::logic_error);
    ASSERT_THROW(*c1 - 123, std::logic_error);
    ASSERT_THROW(*c1 * 123, std::logic_error);
    ASSERT_THROW(*c1 / 123, std::logic_error);

    auto p1 = F.Create("power", -5);
    ASSERT_THROW(*p1 + "123", std::logic_error);
    ASSERT_THROW(*p1 - "123", std::logic_error);
    ASSERT_THROW(*p1 * "123", std::logic_error);
    ASSERT_THROW(*p1 / "123", std::logic_error);
    ASSERT_THROW(*p1 + 123, std::logic_error);
    ASSERT_THROW(*p1 - 123, std::logic_error);
    ASSERT_THROW(*p1 * 123, std::logic_error);
    ASSERT_THROW(*p1 / 123, std::logic_error);

    auto e1 = F.Create("exp", -3);
    ASSERT_THROW(*e1 + "123", std::logic_error);
    ASSERT_THROW(*e1 - "123", std::logic_error);
    ASSERT_THROW(*e1 * "123", std::logic_error);
    ASSERT_THROW(*e1 / "123", std::logic_error);
    ASSERT_THROW(*e1 + 123, std::logic_error);
    ASSERT_THROW(*e1 - 123, std::logic_error);
    ASSERT_THROW(*e1 * 123, std::logic_error);
    ASSERT_THROW(*e1 / 123, std::logic_error);

    auto pol1 = F.Create("polynomial", {1, -2, 0, 3});
    ASSERT_THROW(*pol1 + "123", std::logic_error);
    ASSERT_THROW(*pol1 - "123", std::logic_error);
    ASSERT_THROW(*pol1 * "123", std::logic_error);
    ASSERT_THROW(*pol1 / "123", std::logic_error);
    ASSERT_THROW(*pol1 + 123, std::logic_error);
    ASSERT_THROW(*pol1 - 123, std::logic_error);
    ASSERT_THROW(*pol1 * 123, std::logic_error);
    ASSERT_THROW(*pol1 / 123, std::logic_error);
}

TEST(Function_test, CompositionsOthers)
{
    auto pol1 = F.Create("polynomial", {1, -2, 0, 3});
    auto e1 = F.Create("exp", 5);

    auto comp1 = *e1 * *pol1;
    ASSERT_FLOAT_EQ(comp1(5), exp(5 * 5) * (*pol1)(5));
    ASSERT_THROW(comp1 * e1, std::logic_error);

    ASSERT_FLOAT_EQ((comp1 / *pol1)(1), comp1(1) / (*pol1)(1));

    auto c1 = F.Create("const", 28.0);
    auto pol2 = F.Create("polynomial", {0, -2, -3, 3});
    ASSERT_FLOAT_EQ(((*pol1 - *pol2) / *c1)(5), 2.7142856);
}

TEST(Function_test, CompositionDerivative)
{
    auto p1 = F.Create("polynomial", {1, 1, 1, 1});
    auto p2 = F.Create("polynomial", {-1, -1, -1});

    auto comp1 = (*p1) / (*p2);
    ASSERT_FLOAT_EQ(comp1.GetDeriv(1), -2.0 / 3);

    auto p3 = F.Create("power", 2);
    auto comp2 = ((*p1) + (*p3) + (*p2)) / comp1;
    ASSERT_FLOAT_EQ(comp2.GetDeriv(1), -12.0 / 4);
}

TEST(Function_test, RootFind)
{
    auto f = F.Create("ident", 5);
    ASSERT_TRUE(abs(GradientDescent::FindRoot(f, 1, 0.1, 1000) - 0) < EPS);

    auto g = F.Create("polynomial", {30, -13, 1});
    ASSERT_TRUE(abs(GradientDescent::FindRoot(g, 6, 0.1, 10000) - 3) < EPS);
    ASSERT_TRUE(abs(GradientDescent::FindRoot(g, 20, 0.1, 10000) - 10) < EPS);
}
