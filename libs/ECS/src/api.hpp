/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** api.hpp
*/

#pragma once

#ifdef _WIN32
  #define EXPORT_ECS_SDK_API __declspec(dllexport)
#else
  #define EXPORT_ECS_SDK_API
#endif
