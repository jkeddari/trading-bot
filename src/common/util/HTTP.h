#pragma once

#include <boost/asio/connect.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>

#include <string>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

namespace util{

  class HTTPSession{

    using Request = http::request<http::string_body>;
    using Response = http::response<http::string_body>;

    public:
      void configure(std::string _uri, std::string _api_key, std::string _api_secret, std::string subapi);

      http::response<http::string_body> get(const std::string target);

    private:
      void authentication(http::request<http::string_body>& req);
      http::response<http::string_body> request(http::request<http::string_body> req);

    private:
      net::io_context ioc;
      std::string uri;
      std::string api_key;
      std::string api_secret;
      std::string subapi;

  };
}
