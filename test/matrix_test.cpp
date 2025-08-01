#include <gtest/gtest.h>
#include "matrix.hpp"

class MatrixTest : public::testing::Test {
    protected:
    void SetUp() override {
        Matrix<float> MatA({{1, 2, 3, 4}, {5, 6, 7, 8}});
        MatA_ptr = std::make_unique<Matrix<float>>(MatA);
    }
    std::unique_ptr<Matrix<float>> MatA_ptr;
    std::unique_ptr<Matrix<float>> MatB_ptr;
};

TEST_F(MatrixTest, Constructors){
    EXPECT_NO_THROW(Matrix<float> Test({{1, 2, 3, 4}, {1, 2, 3, 4}}));
    EXPECT_THROW(Matrix<float> Test({{1, 2, 3, 4}, {1, 2, 3}}), std::invalid_argument);
}

TEST_F(MatrixTest, AccessToShape)
{
    EXPECT_NO_THROW(MatA_ptr->shape());
    std::pair<size_t, size_t> shape = MatA_ptr->shape();
    EXPECT_EQ(shape.first, 2);
    EXPECT_EQ(shape.second, 4);
}

TEST_F(MatrixTest, AccessToArray)
{
    for (int i = 0; i < MatA_ptr->shape().first; i++)
    {
        for (int j = 0; j < MatA_ptr->shape().second; j++)
        {
            EXPECT_EQ((*MatA_ptr)[i][j], i * MatA_ptr->shape().second + j + 1);
            // Assign new value
            (*MatA_ptr)[i][j] = (-i) * MatA_ptr->shape().second + j + 1;
        }
    }
    // If Assigned correctly
    for (int i = 0; i < MatA_ptr->shape().first; i++)
    {
        for (int j = 0; j < MatA_ptr->shape().second; j++)
        {
            EXPECT_EQ((*MatA_ptr)[i][j], (-i) * MatA_ptr->shape().second + j + 1);
        }
    }
    EXPECT_THROW((*MatA_ptr)[MatA_ptr->shape().first][0], std::out_of_range);
    EXPECT_THROW((*MatA_ptr)[-1][0], std::out_of_range);
}

TEST_F(MatrixTest, AdditionOfTwoMatrices)
{
    Matrix<float> TestA({{1, 2, 3, 4}, {5, 6, 7, 8}});
    (*MatA_ptr) += TestA;
    for (int i = 0; i < MatA_ptr->shape().first; i++)
    {
       for (int j = 0; j < MatA_ptr->shape().second; j++)
       {
           EXPECT_EQ((*MatA_ptr)[i][j], TestA[i][j] * 2);
       }
    }
    Matrix<float> TestB({{1, 2, 3}, {5, 6, 7}});
    EXPECT_THROW((*MatA_ptr) += TestB, std::invalid_argument);
}

TEST_F(MatrixTest, SubstractionOfTwoMatrices)
{
    Matrix<float> TestA({{1, 2, 3, 4}, {5, 6, 7, 8}});
    (*MatA_ptr) -= TestA;
    for (int i = 0; i < MatA_ptr->shape().first; i++)
    {
       for (int j = 0; j < MatA_ptr->shape().second; j++)
       {
           EXPECT_EQ((*MatA_ptr)[i][j], 0);
       }
    }
    Matrix<float> TestB({{1, 2, 3}, {5, 6, 7}});
    EXPECT_THROW((*MatA_ptr) -= TestB, std::invalid_argument);
}

TEST_F(MatrixTest, ScaleOfMatrix)
{
    Matrix<float> TestA({{1, 2, 3, 4}, {5, 6, 7, 8}});
    (*MatA_ptr) *= 2;
    for (int i = 0; i < MatA_ptr->shape().first; i++)
    {
       for (int j = 0; j < MatA_ptr->shape().second; j++)
       {
           EXPECT_EQ((*MatA_ptr)[i][j], TestA[i][j] * 2);
       }
    }
}