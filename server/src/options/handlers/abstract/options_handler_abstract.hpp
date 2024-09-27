/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** options_handler_abstract.hpp
*/

#pragma once

#include <boost/program_options.hpp>

#include "server/src/options/handlers/options_handler_interface.hpp"

namespace po = boost::program_options;

namespace rtype::server::cli {
class OptionsHandlerAbstract : public IOptionsHandler {
 public:
  OptionsHandlerAbstract();
  ~OptionsHandlerAbstract() override = default;

 protected:
  po::variables_map mVariablesMap;
  po::options_description mDescription;
};

}  // namespace rtype::server::cli
