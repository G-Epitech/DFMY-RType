/*
** EPITECH PROJECT, 2024
** my_sql.cpp
** File description:
** MySQL class
*/

#include "my_sql.hpp"

using namespace abra::database;

MySQL::MySQL(const ConnectionProps &props)
    : sslCtx_(boost::asio::ssl::context::tls_client),
      connection_(ctx_.get_executor(), sslCtx_),
      resolver_(ctx_.get_executor()) {
  this->endpoints_ = resolver_.resolve(props.host, props.port);

  boost::mysql::handshake_params params(props.username, props.password, props.database);
  connection_.connect(*endpoints_.begin(), params);
}

boost::mysql::results MySQL::Execute(const std::string &query) {
  boost::mysql::results result;

  connection_.execute(query, result);
  return result;
}
