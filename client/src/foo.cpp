/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** foo.cpp
*/

#include <fmt/format.h>
#include <iostream>

void foo() {
    std::string name = "John";
    int age = 30;

    fmt::print("Hello, {}! You are {} years old.\n", name, age);
    std::cout << "Client Core lib" << std::endl;
}
