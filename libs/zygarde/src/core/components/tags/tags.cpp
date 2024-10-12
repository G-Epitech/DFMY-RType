/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** tag.cpp
*/

#include "tags.hpp"
using namespace zygarde::core::components;

Tags::Tags(const std::set<std::string>& tags) : tags_{tags} {}

bool Tags::operator==(const std::string& tag) const {
  return tags_.find(tag) != tags_.end();
}

void Tags::AddTag(const std::string& tag) {
  tags_.insert(tag);
}

void Tags::RemoveTag(const std::string& tag) {
  tags_.erase(tag);
}
