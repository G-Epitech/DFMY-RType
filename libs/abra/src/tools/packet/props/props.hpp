/*
** EPITECH PROJECT, 2024
** props.hpp
** File description:
** props class
*/

#pragma once

#include "header.hpp"
#include "message.hpp"
#include "offset.hpp"
#include "turn.hpp"

constexpr unsigned int kPacketMaxBytesSize = (kPacketHeaderPropsSize + kPacketMessagePropsSize +
                                              kPacketOffsetPropsSize + kPacketTurnPropsSize / 8) +
                                             1024;
