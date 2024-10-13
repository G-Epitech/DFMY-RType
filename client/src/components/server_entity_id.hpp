/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** server_entity_id.hpp
*/

#pragma once
#include <cstddef>

namespace rtype::client::components {
/// @brief ServerEntityId Component use in an ECS
struct ServerEntityId {
  std::size_t id;  ///< ID of the entity on the server
};
}  // namespace rtype::client::components
