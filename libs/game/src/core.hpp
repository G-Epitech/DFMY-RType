/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** core.hpp
*/

#pragma once

#ifdef _WIN32
  #define EXPORT_GAME_SDK_API __declspec(dllexport)
#else
  #define EXPORT_GAME_SDK_API
#endif
