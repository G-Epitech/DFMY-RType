/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** tag.cpp
*/

#include "./tags.hpp"
using namespace zygarde::core::components;

Tags::Tags(const std::set<std::string>& tags) : tags_{tags} {}

Tags::~Tags() {
  tags_.clear();
}

bool Tags::operator==(const std::string& tag) const {
  return tags_.contains(tag);
}

bool Tags::operator&(const std::string& tag) const {
  return tags_.contains(tag);
}

void Tags::AddTag(const std::string& tag) {
  tags_.insert(tag);
}

void Tags::RemoveTag(const std::string& tag) {
  tags_.erase(tag);
}

Tags::Tags(Tags&& other) noexcept {
  tags_ = std::move(other.tags_);
}

Tags& Tags::operator=(const Tags& other) {
  tags_ = other.tags_;
  return *this;
}

Tags& Tags::operator=(Tags&& other) noexcept {
  tags_ = std::move(other.tags_);
  return *this;
}

std::set<std::string>& Tags::GetTags() {
  return tags_;
}
