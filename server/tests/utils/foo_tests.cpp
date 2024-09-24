/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** foo_tests.cpp
*/

#include "src/foo.hpp"
#include <gtest/gtest.h>

TEST(AddFunctionTest, HandlesPositiveNumbers) {
    EXPECT_EQ(add(2, 3), 5);
    EXPECT_EQ(add(10, 20), 30);
}
