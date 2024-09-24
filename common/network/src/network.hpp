/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** network.hpp
*/

#pragma once

#ifdef _WIN32
#define NETWORK_COMMON_API __declspec(dllexport)
#else
#define NETWORK_COMMON_API
#endif

NETWORK_COMMON_API void network();
