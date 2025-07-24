#include <gtest/gtest.h>
#include "vector.hpp"

class VectorTest : public::testing::Test {
  protected:
    void SetUp() override {
      one = {1, 2, 3};
      two = {4, 5, 6};
      VecA = std::make_unique<Vector<float>>(one);
      VecB = std::make_unique<Vector<float>>(two);
    }
    std::vector<float> one;
    std::vector<float> two;
    std::unique_ptr<Vector<float>> VecA;
    std::unique_ptr<Vector<float>> VecB;
};

TEST_F(VectorTest, Constructors) {
  std::vector<float> test({1, 2, 3});
  EXPECT_NO_THROW(Vector<float> Test(test));
  std::vector<float> testTwo;
  EXPECT_THROW(Vector<float> Test2(testTwo), std::length_error);
}

TEST_F(VectorTest, AccessToList)
{
  for (int i = 0; i < 3; i++)
  {
    EXPECT_NO_THROW((*VecA)[i]);
    EXPECT_EQ((*VecA)[i], i + 1);
  }
  EXPECT_THROW((*VecA)[4], std::out_of_range);
  EXPECT_THROW((*VecA)[-1], std::out_of_range);

}

TEST_F(VectorTest, AccessToSize)
{
  EXPECT_NO_THROW(VecA->shape());
  EXPECT_EQ(VecA->shape(), 3);
}

TEST_F(VectorTest, AccessThroughIndex)
{
  EXPECT_NO_THROW((*VecA)[0]);
  EXPECT_THROW((*VecA)[VecA->shape()], std::out_of_range);
  EXPECT_THROW((*VecA)[-1], std::out_of_range);

}

TEST_F(VectorTest, ModifyingThroughIndex)
{
  EXPECT_NO_THROW((*VecA)[0] = -1);
  EXPECT_EQ((*VecA)[0], -1);

}

TEST_F(VectorTest, AdditionOfTwoVectors)
{
  EXPECT_NO_THROW(*VecA += *VecB);
  for (int i = 0; i < VecA->shape(); i++)
  {
    EXPECT_EQ(one[i] + two[i], (*VecA)[i]);
  }
  std::vector<float> test({1, 2, 3, 4});
  Vector<float> WrongSizedVector(test);
  EXPECT_THROW(*VecA += WrongSizedVector, std::length_error);
}

TEST_F(VectorTest, SubstractionOfTwoVectors)
{
  EXPECT_NO_THROW(*VecA -= *VecB);
  for (int i = 0; i < VecA->shape(); i++)
  {
    EXPECT_EQ(one[i] - two[i], (*VecA)[i]);
  }
  std::vector<float> test({1, 2, 3, 4});
  Vector<float> WrongSizedVector(test);
  EXPECT_THROW(*VecA -= WrongSizedVector, std::length_error);
}

TEST_F(VectorTest, ScaleVector)
{
  float scalar = 2.1;
  EXPECT_NO_THROW(*VecA *= scalar);
  for (int i = 0; i < VecA->shape(); i++)
  {
    EXPECT_EQ(one[i] * scalar, (*VecA)[i]);
  }
}