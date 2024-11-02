/*
** EPITECH PROJECT, 2024
** my_sql.hpp
** File description:
** MySQL class
*/

#pragma once

#include <boost/mysql.hpp>
#include <string>

#include "libs/abra/src/core.hpp"

namespace abra::database {
class EXPORT_NETWORK_SDK_API MySQL;
}

class abra::database::MySQL {
 public:
  /// @brief The database connection properties
  struct ConnectionProps {
    std::string host;
    std::string port = boost::mysql::default_port_string;
    std::string username;
    std::string password;
    std::string database;
  };

  /**
   * @brief Construct a new MySQL object
   * @param props The connection properties
   */
  explicit MySQL(const ConnectionProps &props);

  /**
   * @brief Execute a query
   * @param query The query to execute
   * @return The results of the query
   */
  boost::mysql::results Execute(const std::string &query);

 private:
  /// @brief The MySQL IO context
  boost::asio::io_context ctx_;

  /// @brief The MySQL SSL context
  boost::asio::ssl::context sslCtx_;

  /// @brief The MySQL connection resolver
  boost::asio::ip::tcp::resolver resolver_;

  /// @brief The MySQL Endpoints
  boost::asio::ip::tcp::resolver::results_type endpoints_;

  /// @brief The MySQL connection
  boost::mysql::tcp_ssl_connection connection_;
};
