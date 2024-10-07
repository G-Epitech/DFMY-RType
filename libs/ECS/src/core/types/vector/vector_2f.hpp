/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** vector_2_f.hpp
*/

#pragma once

namespace rtype::sdk::ECS::core::types {
class vector_2f {
 public:
  vector_2f() = default;

  ~vector_2f() = default;

  vector_2f(float x, float y);
  vector_2f(const vector_2f &vec) = default;
  vector_2f(vector_2f &&vec) noexcept = default;

 public:
  vector_2f &operator=(const vector_2f &vec) = default;
  vector_2f &operator=(vector_2f &&vec) noexcept = default;
  vector_2f operator+(const vector_2f &vec) const;
  vector_2f &operator+=(const vector_2f &vec);
  vector_2f operator-(const vector_2f &vec) const;
  vector_2f operator-=(const vector_2f &vec);

 public:
  float x;
  float y;
};
}
