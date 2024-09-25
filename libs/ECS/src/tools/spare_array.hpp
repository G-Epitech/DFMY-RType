/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** spare_array.hpp
*/

#pragma once

#include <vector>
#include <cstddef>
#include <optional>

namespace rtype {
  template<typename Component>
  class sparse_array {
  public :
    using value_type = std::optional<Component>;
    using reference_type = value_type &;
    using const_reference_type = value_type const &;
    using container_t = std::vector<value_type>;
    using size_type = typename container_t::size_type;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

  public :
    sparse_array();

    sparse_array(sparse_array const &);

    sparse_array(sparse_array &&) noexcept;

    ~sparse_array();

    sparse_array &operator=(sparse_array const &);

    sparse_array &operator=(sparse_array &&) noexcept;

    reference_type operator[](size_t idx);

    const_reference_type operator[](size_t idx) const;

    iterator begin();

    const_iterator begin() const;

    const_iterator cbegin() const;

    iterator end();

    const_iterator end() const;

    const_iterator cend() const;

    size_type size() const;

    reference_type insert_at(size_type pos, Component const &);

    reference_type insert_at(size_type pos, Component &&);

    template<class... Params>
    reference_type emplace_at(size_type pos, Params &&...);

    void erase(size_type pos);

    size_type get_index(value_type const &) const;

    void resize(size_type new_size);

    void shrink_to_fit();

  private :
    container_t _data;
  };
} // rtype

#include "spare_array.tpp"
