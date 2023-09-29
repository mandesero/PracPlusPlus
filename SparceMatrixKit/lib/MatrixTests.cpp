#include "gtest/gtest.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"

TEST(Matrix_TestSuite, Matrix_0)
{
    /**
     * Ввод матрицы с файла (без исключений) [map | unordered_map]
     */

    auto m_1 = Matrix<std::map, Complex_number<double, int32_t>>::readFromFile("input/in_matrix_3");
    Matrix<std::map, Complex_number<double, int32_t>> matrix_1(6, 4);
    matrix_1[std::make_pair(2, 1)] = Complex_number<double, int32_t>(82);
    matrix_1[std::make_pair(3, 2)] = Complex_number<double, int32_t>(54, 12);
    matrix_1[std::make_pair(4, 1)] = Complex_number<double, int32_t>(221, 321);
    matrix_1[std::make_pair(4, 3)] = Complex_number<double, int32_t>(99, 320);
    matrix_1[std::make_pair(5, 1)] = Complex_number<double, int32_t>(382, 616);
    matrix_1[std::make_pair(5, 2)] = Complex_number<double, int32_t>(472, 104);
    matrix_1[std::make_pair(5, 3)] = Complex_number<double, int32_t>(72);

    EXPECT_EQ(m_1.to_string(), matrix_1.to_string());

    auto m_2 = Matrix<std::unordered_map, Complex_number<double, int32_t>>::readFromFile("input/in_matrix_3");
    Matrix<std::unordered_map, Complex_number<double, int32_t>> matrix_2(6, 4);
    matrix_2[std::make_pair(2, 1)] = Complex_number<double, int32_t>(82);
    matrix_2[std::make_pair(3, 2)] = Complex_number<double, int32_t>(54, 12);
    matrix_2[std::make_pair(4, 1)] = Complex_number<double, int32_t>(221, 321);
    matrix_2[std::make_pair(4, 3)] = Complex_number<double, int32_t>(99, 320);
    matrix_2[std::make_pair(5, 1)] = Complex_number<double, int32_t>(382, 616);
    matrix_2[std::make_pair(5, 2)] = Complex_number<double, int32_t>(472, 104);
    matrix_2[std::make_pair(5, 3)] = Complex_number<double, int32_t>(72);

    EXPECT_EQ(m_2.to_string(), matrix_2.to_string());

    /**
     * Ввод матрицы с файла (файл не содержащий матрицу) [map | unordered_map]
     */

    EXPECT_THROW((Matrix<std::map, Complex_number<double, int32_t>>::readFromFile("input/in_vector_2")), MatrixReadFromFileError);
    EXPECT_THROW((Matrix<std::unordered_map, Complex_number<double, int32_t>>::readFromFile("input/in_vector_2")), MatrixReadFromFileError);

    /**
     * Ввод матрицы с файла (неправильный тип аргументов) [map | unordered_map]
     */

    EXPECT_THROW((Matrix<std::map, Rational_number<int64_t>>::readFromFile("input/in_vector_2")), MatrixReadFromFileError);
    EXPECT_THROW((Matrix<std::unordered_map, Rational_number<int64_t>>::readFromFile("input/in_vector_2")), MatrixReadFromFileError);

    /**
     * Ввод матрицы с файла (переполнение) [map | unordered_map]
     */

    EXPECT_THROW((Matrix<std::map, Rational_number<int8_t>>::readFromFile("input/in_matrix_1")), RationalOverflowError<int64_t>);
    EXPECT_THROW((Matrix<std::unordered_map, Rational_number<int8_t>>::readFromFile("input/in_matrix_1")), RationalOverflowError<int64_t>);
}

TEST(Matrix_TestSuite, Matrix_1)
{
    /*
        Static конструкторы [eye, ones, zeros]
    */
    auto matrix_1 = Matrix<std::unordered_map, Rational_number<int64_t>>::eye(3, 4);
    Matrix<std::unordered_map, Rational_number<int64_t>> m_1(3, 4);
    m_1[std::make_pair(1, 1)] = Rational_number<int64_t>(1);
    m_1[std::make_pair(2, 2)] = Rational_number<int64_t>(1);
    m_1[std::make_pair(3, 3)] = Rational_number<int64_t>(1);

    EXPECT_EQ(matrix_1.to_string(), m_1.to_string());

    auto matrix_2 = Matrix<std::map, Rational_number<int64_t>>::ones(2, 2);
    Matrix<std::map, Rational_number<int64_t>> m_2(2, 2);
    m_2[std::make_pair(1, 1)] = Rational_number<int64_t>(1);
    m_2[std::make_pair(2, 2)] = Rational_number<int64_t>(1);
    m_2[std::make_pair(2, 1)] = Rational_number<int64_t>(1);
    m_2[std::make_pair(1, 2)] = Rational_number<int64_t>(1);

    EXPECT_EQ(matrix_2.to_string(), m_2.to_string());

    auto matrix_3 = Matrix<std::unordered_map, Rational_number<int64_t>>::zeros(2, 2);
    Matrix<std::unordered_map, Rational_number<int64_t>> m_3(2, 2);
    m_3[std::make_pair(1, 1)] = Rational_number<int64_t>();
    m_3[std::make_pair(2, 2)] = Rational_number<int64_t>();
    m_3[std::make_pair(2, 1)] = Rational_number<int64_t>();
    m_3[std::make_pair(1, 2)] = Rational_number<int64_t>();

    EXPECT_EQ(matrix_3.to_string(), m_3.to_string());
}

TEST(Matrix_TestSuite, Matrix_2)
{
    /**
     * операции + - *, унарный -, транспонирование ~
     */
    Matrix<std::map, Rational_number<int64_t>> m_1(2, 2);
    m_1[std::make_pair(1, 1)] = Rational_number<int64_t>("2/3");
    m_1[std::make_pair(2, 2)] = Rational_number<int64_t>("3/4");
    m_1[std::make_pair(2, 1)] = Rational_number<int64_t>("4/5");
    m_1[std::make_pair(1, 2)] = Rational_number<int64_t>("5/6");

    auto m_2 = Matrix<std::map, Rational_number<int64_t>>::ones(2, 2);

    Matrix<std::map, Rational_number<int64_t>> r_1(2, 2);
    r_1[std::make_pair(1, 1)] = Rational_number<int64_t>("5/3");
    r_1[std::make_pair(2, 2)] = Rational_number<int64_t>("7/4");
    r_1[std::make_pair(2, 1)] = Rational_number<int64_t>("9/5");
    r_1[std::make_pair(1, 2)] = Rational_number<int64_t>("11/6");

    EXPECT_EQ((m_1 + m_2).to_string(), r_1.to_string());

    Matrix<std::map, Rational_number<int64_t>> r_2(2, 2);
    r_2[std::make_pair(1, 1)] = Rational_number<int64_t>("-1/3");
    r_2[std::make_pair(2, 2)] = Rational_number<int64_t>("-1/4");
    r_2[std::make_pair(2, 1)] = Rational_number<int64_t>("-1/5");
    r_2[std::make_pair(1, 2)] = Rational_number<int64_t>("-1/6");

    EXPECT_EQ((m_1 - m_2).to_string(), r_2.to_string());

    Matrix<std::map, Rational_number<int64_t>> r_3(2, 2);
    r_3[std::make_pair(1, 1)] = Rational_number<int64_t>("27/18");
    r_3[std::make_pair(1, 2)] = Rational_number<int64_t>("27/18");
    r_3[std::make_pair(2, 1)] = Rational_number<int64_t>("31/20");
    r_3[std::make_pair(2, 2)] = Rational_number<int64_t>("31/20");

    EXPECT_EQ((m_1 * m_2).to_string(), r_3.to_string());

    Matrix<std::map, Rational_number<int64_t>> r_4(2, 2);
    r_4[std::make_pair(1, 1)] = Rational_number<int64_t>("2/3");
    r_4[std::make_pair(1, 2)] = Rational_number<int64_t>("4/5");
    r_4[std::make_pair(2, 1)] = Rational_number<int64_t>("5/6");
    r_4[std::make_pair(2, 2)] = Rational_number<int64_t>("3/4");

    EXPECT_EQ((~m_1).to_string(), r_4.to_string());
}

TEST(Matrix_TestSuite, Matrix_3)
{
    /**
     * Доступ к элементам по индексам, умножение матрицы на вектор и вектора на матрицу, приведение к строке to_sting()
     */
    auto m_1 = Matrix<std::unordered_map, Rational_number<int64_t>>::ones(2, 2);
    EXPECT_EQ(m_1[std::make_pair(1, 1)], Rational_number<int64_t>(1));

    m_1[std::make_pair(1, 1)] = Rational_number<int64_t>("55/11");
    EXPECT_EQ(m_1[std::make_pair(1, 1)], Rational_number<int64_t>("55/11"));

    Vector<Rational_number<int64_t>> v_1(2);
    v_1[1] = Rational_number<int64_t>(2);
    v_1[2] = Rational_number<int64_t>(3);

    Vector<Rational_number<int64_t>> ans_1(2);
    ans_1[1] = Rational_number<int64_t>("143/11");
    ans_1[2] = Rational_number<int64_t>("5/1");

    EXPECT_EQ((m_1 * v_1).to_string(), ans_1.to_string());
    EXPECT_EQ((v_1 * ~m_1).to_string(), ans_1.to_string());
}

TEST(Matrix_TestSuite, Matrix_4)
{
    /**
     * Срезы, прокси, обращание к элементу прокси по индексу [ind], преобразование к прокси к вектору
     */
    auto m_1 = Matrix<std::map, Complex_number<int64_t>>::ones(5, 5);
    auto m_2 = Matrix<std::map, Complex_number<int64_t>>::ones(2, 3);
    auto m_3 = Matrix<std::map, Complex_number<int64_t>>::ones(4, 3);

    EXPECT_EQ(
        m_1[Matrix_coords(-1, 2, 3, -1)].to_string(),
        m_1.to_string());

    EXPECT_EQ(
        m_1[Matrix_coords(1, 1, 2, 3)].to_string(),
        m_2.to_string());

    EXPECT_EQ(
        m_1[Matrix_coords(1, 1, 2, 3)][Matrix_coords(1, 1, 4, 3)].to_string(),
        m_3.to_string());

    Matrix<std::map, Rational_number<int64_t>> m_4(2, 2);
    m_4[std::make_pair(1, 1)] = Rational_number<int64_t>("2/3");
    m_4[std::make_pair(2, 2)] = Rational_number<int64_t>("3/4");
    m_4[std::make_pair(2, 1)] = Rational_number<int64_t>("4/5");
    m_4[std::make_pair(1, 2)] = Rational_number<int64_t>("5/6");

    auto pr_1 = m_4[Matrix_column_coord(2)];
    auto pr_2 = m_4[Matrix_row_coord(1)];

    EXPECT_EQ(
        pr_1.to_string(),
        "5/6\n3/4\n");

    EXPECT_EQ(
        pr_2.to_string(),
        "2/3 5/6 ");

    EXPECT_EQ(
        pr_1[2],
        Rational_number<int64_t>("3/4"));

    EXPECT_EQ(
        pr_2[1],
        Rational_number<int64_t>("2/3"));

    Vector<Rational_number<int64_t>> v_1(2);
    v_1[1] = Rational_number<int64_t>("2/3");
    v_1[2] = Rational_number<int64_t>("5/6");

    EXPECT_EQ(
        pr_2.create_vector().to_string(),
        v_1.to_string());

    Vector<Rational_number<int64_t>> v_2(2);
    v_2[1] = Rational_number<int64_t>("5/6");
    v_2[2] = Rational_number<int64_t>("3/4");

    EXPECT_EQ(
        pr_1.create_vector(),
        v_2);
}

TEST(Matrix_TestSuite, Matrix_5)
{
    /**
     *  Исключения
     */
    auto m_1 = Matrix<std::unordered_map, Complex_number<int64_t>>::ones(5, 5);
    auto m_2 = Matrix<std::unordered_map, Complex_number<int64_t>>::ones(2, 3);

    Vector<Complex_number<int64_t>> v_1(2);
    v_1[1] = Complex_number<int64_t>("5/6");
    v_1[2] = Complex_number<int64_t>("3/4");

    EXPECT_THROW(m_1 + m_2, MatrixShapeError);
    EXPECT_THROW(m_1 * m_2, MatrixShapeError);
    EXPECT_THROW(m_1 * v_1, MatrixShapeError);
    EXPECT_THROW(v_1 * m_1, MatrixShapeError);

    EXPECT_THROW(m_1(123, 412), MatrixIndexError);

    auto x = m_1[Matrix_row_coord(2)];

    EXPECT_THROW(x[11337], ProxyIndexError);

    auto mmm = new Matrix<std::unordered_map, Complex_number<int64_t>>(4,4);
    auto pr_mmm = mmm->operator[](Matrix_column_coord(3));
    delete mmm;
    EXPECT_THROW(pr_mmm[1], ProxyPointerError);

}