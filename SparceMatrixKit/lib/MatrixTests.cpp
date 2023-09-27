#include "gtest/gtest.h"
#include "Rational.h"
#include "Complex.h"
#include "Vector.h"
#include "Matrix.h"

TEST(Matrix_TestSuite, Matrix_0)
{
    /**
     * Ввод матрицы и ветора с файла, генерация матриц eye, once, zeros
     */
    // std::string filename = "input/in_matrix_3";
    // std::ifstream file(filename);
    // StreamNumber meta = readFromFile(file);
    // auto m = getCM_if(meta, file);
    // Matrix<Complex_number<int64_t, double>> matrix(6, 4);
    // matrix[std::make_pair(2, 1)] = Complex_number<int64_t, double>(82);
    // matrix[std::make_pair(3, 2)] = Complex_number<int64_t, double>(54, 12);
    // matrix[std::make_pair(4, 1)] = Complex_number<int64_t, double>(221, 321);
    // matrix[std::make_pair(4, 3)] = Complex_number<int64_t, double>(99, 320);
    // matrix[std::make_pair(5, 1)] = Complex_number<int64_t, double>(382, 616);
    // matrix[std::make_pair(5, 2)] = Complex_number<int64_t, double>(472, 104);
    // matrix[std::make_pair(5, 3)] = Complex_number<int64_t, double>(72);

    // EXPECT_EQ(m, matrix);

    // std::string filename_1 = "input/in_vector_1";
    // std::ifstream file_1(filename_1);
    // StreamNumber meta_1 = readFromFile(file_1);
    // auto v_0 = getCV_ff(meta_1, file_1);

    // Vector<Complex_number<double>> v_1(20);
    // v_1[6] = Complex_number<double>(71, 386);
    // v_1[7] = Complex_number<double>(39, 777);
    // v_1[13] = Complex_number<double>(23, 674);
    // v_1[14] = Complex_number<double>(257, 114);
    // v_1[15] = Complex_number<double>(380, 172);
    // v_1[17] = Complex_number<double>(729, 975);

    // EXPECT_EQ(v_0, v_1);

    auto matrix_2 = Matrix<Rational_number<int64_t>>::eye(3, 4);
    Matrix<Rational_number<int64_t>> m_2(3, 4);
    m_2[std::make_pair(1, 1)] = Rational_number<int64_t>(1);
    m_2[std::make_pair(2, 2)] = Rational_number<int64_t>(1);
    m_2[std::make_pair(3, 3)] = Rational_number<int64_t>(1);

    EXPECT_EQ(matrix_2, m_2);

    auto matrix_3 = Matrix<Rational_number<int64_t>>::ones(2, 2);
    Matrix<Rational_number<int64_t>> m_3(2, 2);
    m_3[std::make_pair(1, 1)] = Rational_number<int64_t>(1);
    m_3[std::make_pair(2, 2)] = Rational_number<int64_t>(1);
    m_3[std::make_pair(2, 1)] = Rational_number<int64_t>(1);
    m_3[std::make_pair(1, 2)] = Rational_number<int64_t>(1);

    EXPECT_EQ(matrix_3, m_3);

    auto matrix_4 = Matrix<Rational_number<int64_t>>::zeros(2, 2);
    Matrix<Rational_number<int64_t>> m_4(2, 2);
    m_4[std::make_pair(1, 1)] = Rational_number<int64_t>();
    m_4[std::make_pair(2, 2)] = Rational_number<int64_t>();
    m_4[std::make_pair(2, 1)] = Rational_number<int64_t>();
    m_4[std::make_pair(1, 2)] = Rational_number<int64_t>();

    EXPECT_EQ(matrix_4, m_4);
}

TEST(Matrix_TestSuite, Matrix_1)
{
    /**
     * операции + - *, унарный -, транспонирование ~
     */
    Matrix<Rational_number<int64_t>> m_1(2, 2);
    m_1[std::make_pair(1, 1)] = Rational_number<int64_t>("2/3");
    m_1[std::make_pair(2, 2)] = Rational_number<int64_t>("3/4");
    m_1[std::make_pair(2, 1)] = Rational_number<int64_t>("4/5");
    m_1[std::make_pair(1, 2)] = Rational_number<int64_t>("5/6");

    auto m_2 = Matrix<Rational_number<int64_t>>::ones(2, 2);

    Matrix<Rational_number<int64_t>> r_1(2, 2);
    r_1[std::make_pair(1, 1)] = Rational_number<int64_t>("5/3");
    r_1[std::make_pair(2, 2)] = Rational_number<int64_t>("7/4");
    r_1[std::make_pair(2, 1)] = Rational_number<int64_t>("9/5");
    r_1[std::make_pair(1, 2)] = Rational_number<int64_t>("11/6");

    EXPECT_EQ(m_1 + m_2, r_1);

    Matrix<Rational_number<int64_t>> r_2(2, 2);
    r_2[std::make_pair(1, 1)] = Rational_number<int64_t>("-1/3");
    r_2[std::make_pair(2, 2)] = Rational_number<int64_t>("-1/4");
    r_2[std::make_pair(2, 1)] = Rational_number<int64_t>("-1/5");
    r_2[std::make_pair(1, 2)] = Rational_number<int64_t>("-1/6");

    EXPECT_EQ(m_1 - m_2, r_2);

    Matrix<Rational_number<int64_t>> r_3(2, 2);
    r_3[std::make_pair(1, 1)] = Rational_number<int64_t>("27/18");
    r_3[std::make_pair(1, 2)] = Rational_number<int64_t>("27/18");
    r_3[std::make_pair(2, 1)] = Rational_number<int64_t>("31/20");
    r_3[std::make_pair(2, 2)] = Rational_number<int64_t>("31/20");

    EXPECT_EQ(m_1 * m_2, r_3);

    Matrix<Rational_number<int64_t>> r_4(2, 2);
    r_4[std::make_pair(1, 1)] = Rational_number<int64_t>("2/3");
    r_4[std::make_pair(1, 2)] = Rational_number<int64_t>("4/5");
    r_4[std::make_pair(2, 1)] = Rational_number<int64_t>("5/6");
    r_4[std::make_pair(2, 2)] = Rational_number<int64_t>("3/4");

    EXPECT_EQ(~m_1, r_4);
}

TEST(Matrix_TestSuite, Matrix_2)
{
    /**
     * Доступ к элементам по индексам, умножение матрицы на вектор и вектора на матрицу, приведение к строке to_sting()
     */
    auto m_1 = Matrix<Rational_number<int64_t>>::ones(2, 2);
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

TEST(Matrix_TestSuite, Matrix_3)
{
    /**
     * Срезы, прокси, обращание к элементу прокси по индексу [ind], преобразование к прокси к вектору
     */
    auto m_1 = Matrix<Complex_number<int64_t>>::ones(5, 5);
    auto m_2 = Matrix<Complex_number<int64_t>>::ones(2, 3);
    auto m_3 = Matrix<Complex_number<int64_t>>::ones(4, 3);

    EXPECT_EQ(
        m_1[Matrix_coords(-1, 2, 3, -1)].to_string(),
        m_1.to_string());

    EXPECT_EQ(
        m_1[Matrix_coords(1, 1, 2, 3)].to_string(),
        m_2.to_string());

    EXPECT_EQ(
        m_1[Matrix_coords(1, 1, 2, 3)][Matrix_coords(1, 1, 4, 3)].to_string(),
        m_3.to_string());

    Matrix<Rational_number<int64_t>> m_4(2, 2);
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

TEST(Matrix_TestSuite, Matrix_4)
{
    /**
     *  Исключения
     */
    auto m_1 = Matrix<Complex_number<int64_t>>::ones(5, 5);
    auto m_2 = Matrix<Complex_number<int64_t>>::ones(2, 3);

    Vector<Complex_number<int64_t>> v_1(2);
    v_1[1] = Complex_number<int64_t>("5/6");
    v_1[2] = Complex_number<int64_t>("3/4");

    EXPECT_ANY_THROW(m_1 + m_2);
    EXPECT_ANY_THROW(m_1 * m_2);
    EXPECT_ANY_THROW(m_1 * v_1);
    EXPECT_ANY_THROW(v_1 * m_1);
}