/*
** EPITECH PROJECT, 2024
** r-type
** File description:
** radio.hpp
*/

#pragma once

#include <string>
#include <variant>

#include "libs/zygarde/src/tools/spare_array.hpp"

namespace rtype::client::components {
    struct Radio {
        using ValueType = std::optional<std::variant<int, std::string>>;

        struct Utils {
            /**
             * @brief Get the value of a radio
             * @param radios Radios sparse array
             * @param id Id of the expected radio
             * @return Current value of the radio
             */
            static ValueType GetValue(const zygarde::tools::sparse_array<Radio>::ptr &radios, const std::string &id);

            /**
             * @brief Set the value of a radio
             * @param radios Radios sparse array
             * @param id Id of the radio to set
             * @param value Value to set
             * @return New value of the radio
             */
            static ValueType
            SetValue(const zygarde::tools::sparse_array<Radio>::ptr &radios, const std::string &id,
                     const ValueType &value);
        };

        std::string id;                       ///< Id of the radio
        ValueType value;                      ///< Value of the radio
        bool selected = false;                ///< Is the radio selected
    };
}
