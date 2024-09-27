/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** config.tpp
*/

#include <iostream>
#include <stdexcept>

template <class T>
T rtype::server::Env::Get(const std::string &key) {
  try {
    return std::any_cast<T>(mEnv.at(key));
  } catch (const std::bad_any_cast &exception) {
    throw std::runtime_error("Incorrect casting for key '" + key + "'");
  }
}
