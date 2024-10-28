/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** abi.hpp
*/

#pragma once

#ifdef __GNUG__
  #include <cxxabi.h>
#endif

#include <memory>
#include <string>
#include <typeinfo>

namespace mew::utils {
template <typename T>
inline std::string GetTypeName() {
  const char* mangled_name = typeid(T).name();

#ifdef __GNUG__
  int status = 0;
  std::unique_ptr<char, void (*)(void*)> demangled_name(
      abi::__cxa_demangle(mangled_name, nullptr, nullptr, &status), std::free);
  return (status == 0) ? demangled_name.get() : mangled_name;
#else
  return mangled_name;
#endif
}
}  // namespace mew::utils
