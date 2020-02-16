#include "common/util/HTTP.h"
#include "common/util/Encoding.h"
#include "common/util/Time.h"
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/version.hpp>

#include <iostream>

namespace ssl = boost::asio::ssl;
using tcp = net::ip::tcp;

namespace util {

    void HTTPSession::configure(std::string uri, std::string api_key, std::string api_secret, std::string subapi) {
        this->uri = uri;
        this->api_key = api_key;
        this->api_secret = api_secret;
        this->subapi = subapi;

    }
    
    http::response<http::string_body> HTTPSession::get(const std::string target){
        std::string endpoint = subapi + target;
        http::request<http::string_body> req{http::verb::get, endpoint, 11};

        return request(req);
    }

    http::response<http::string_body> HTTPSession::request(http::request<http::string_body> req){
        req.set(http::field::host, uri.c_str());
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        std::cout << req << "\n";
        
        ssl::context ctx{ssl::context::sslv23_client};
        ctx.set_default_verify_paths();


        

        tcp::resolver resolver{ioc};
        ssl::stream<tcp::socket> stream{ioc, ctx};

        // Set SNI Hostname (many hosts need this to handshake successfully)
        if (!SSL_set_tlsext_host_name(stream.native_handle(), uri.c_str())) {
            boost::system::error_code ec{
                static_cast<int>(::ERR_get_error()),net::error::get_ssl_category()
            };
            throw boost::system::system_error{ec};
        }

        auto const results = resolver.resolve(uri.c_str(), "443");
        net::connect(stream.next_layer(), results.begin(), results.end());
        stream.handshake(ssl::stream_base::client);

        

        authentication(req);

        if (req.method() == http::verb::post) {
            req.set(http::field::content_type, "application/json");
        }

        std::cout << req << "\n";

        http::write(stream, req);
        boost::beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(stream, buffer, response);

        boost::system::error_code ec;
        stream.shutdown(ec);
        if (ec == boost::asio::error::eof) {
            ec.assign(0, ec.category());
        }

        return response;
    }

    void HTTPSession::authentication(http::request<http::string_body>& req){
        req.set("X-MBX-APIKEY", api_key);
    }
    
}
