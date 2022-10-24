//
// Created by delmwin on 10/24/22.
//

#include "gtest/gtest.h"

class ExampleFixture : public ::testing::Test {

protected:
    void SetUp() override {
        test = new int;
        *test = 1;
    }

    void TearDown() override {
        delete test;
    }

    int *test{};
};

TEST_F(ExampleFixture, Test1) {
    EXPECT_EQ(*test, 1);
}
