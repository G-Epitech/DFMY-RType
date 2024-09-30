/*
** EPITECH PROJECT, 2024
** dynamic_bitset.cpp
** File description:
** dynamic_bitset class
*/

#include "dynamic_bitset.hpp"

using namespace rtype::sdk::network;

tools::dynamic_bitset::dynamic_bitset(std::size_t size) : mSize(size), mBitset((size + 7) / 8, 0) {}

tools::dynamic_bitset::~dynamic_bitset() = default;

void tools::dynamic_bitset::Set(std::size_t index, bool value) {
  std::size_t byteIndex = index / 8;
  std::size_t bitIndex = index % 8;

  if (value) {
    mBitset[byteIndex] |= (1 << bitIndex);
  } else {
    mBitset[byteIndex] &= ~(1 << bitIndex);
  }
}

bool tools::dynamic_bitset::Get(std::size_t index) const {
  size_t byteIndex = index / 8;
  size_t bitIndex = index % 8;

  return (mBitset[byteIndex] >> bitIndex) & 1;
}

std::size_t tools::dynamic_bitset::GetSize() const {
  return mSize;
}

void tools::dynamic_bitset::Append(unsigned int value, std::size_t size, std::size_t offset) {
  for (std::size_t i = 0; i < size; i++) {
    Set(offset + i, (value >> (size - 1 - i)) & 1);
  }
}

void tools::dynamic_bitset::FillFromRange(std::size_t start, std::size_t end,
                                          unsigned int &value) const {
  for (std::size_t i = start; i < end; i++) {
    value = (value << 1) | Get(i);
  }
}

std::ostream &operator<<(std::ostream &os,
                         const rtype::sdk::network::tools::dynamic_bitset &bitset) {
  for (std::size_t i = 0; i < bitset.GetSize(); i++) {
    if (i % 8 == 0)
      os << ".";

    os << bitset.Get(i ? 1 : 0);
  }
  return os;
}
