/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** network.hpp
*/

#pragma once

#ifdef _WIN32
    #define EXPORT_NETWORK_SDK_API __declspec(dllexport)
#else
    #define EXPORT_NETWORK_SDK_API
#endif

EXPORT_NETWORK_SDK_API void network();
