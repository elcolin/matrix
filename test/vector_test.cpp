#include <gtest/gtest.h>
#include "vector.hpp"
#include "linear_algebra.hpp"

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
  EXPECT_THROW(Vector<float> Test2(testTwo), std::invalid_argument);
  EXPECT_NO_THROW(Vector<float> Test3({1, 2, 3, 4}));

}

TEST_F(VectorTest, AccessToArray)
{
  for (int i = 0; i < 3; i++)
  {
    EXPECT_NO_THROW((*VecA)[i]);
    EXPECT_EQ((*VecA)[i], i + 1);
  }
  Vector<float> arrayTest({1, 2, 3});
  for (int i = 0; i < 3; i++)
  {
    EXPECT_NO_THROW(arrayTest[i]);
    EXPECT_EQ(arrayTest[i], i + 1);
  }
  EXPECT_THROW((*VecA)[4], std::out_of_range);
  EXPECT_THROW(arrayTest[4], std::out_of_range);
  EXPECT_THROW((*VecA)[-1], std::out_of_range);
  EXPECT_THROW(arrayTest[-1], std::out_of_range);
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
  EXPECT_THROW(*VecA += WrongSizedVector, std::invalid_argument);
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
  EXPECT_THROW(*VecA -= WrongSizedVector, std::invalid_argument);
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

TEST_F(VectorTest, VectorsEquality)
{
  Vector<float> WrongSize({1, 2});
  EXPECT_THROW(void((*VecA) == WrongSize), std::invalid_argument);
  Vector<float> EqualVector({1, 2, 3});
  EXPECT_TRUE((*VecA) == EqualVector);
  EXPECT_FALSE((*VecA) == (*VecB));
}

TEST_F(VectorTest, LinearCombination)
{
  Vector<float> e1({1., 0, 0});
  Vector<float> e2({0, 1., 0});
  Vector<float> e3({0, 0, 1.});

  Vector<float> v1({1, 2, 3});
  Vector<float> v2({0, 10, -100});

  Vector<float> res1({10, -2, 0.5});
  Vector<float> res2({10, 0, 230});

  Vector<float> wrongSize({1, 2});

  EXPECT_TRUE(linear_combination(std::vector{e1, e2, e3}, {10., -2., 0.5}) == res1);
  EXPECT_TRUE(linear_combination(std::vector{v1, v2}, {10, -2}) == res2);
  EXPECT_THROW(linear_combination(std::vector{e1, e2}, {1}), std::invalid_argument);
  EXPECT_THROW(linear_combination(std::vector{e1, wrongSize}, {1, 2}), std::invalid_argument);
}

TEST_F(VectorTest, LinearInterpolation)
{

}