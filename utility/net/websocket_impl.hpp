#pragma once
#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include "protocol.hpp"
#include <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace asio = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

class WebSocketImpl : public Protocol {
public:
    WebSocketImpl(boost::asio::io_context& ioc)
        : resolver_(ioc), ws_(ioc) {
            std::cout << "init websocket" << std::endl;
        }

    bool connect(const std::string& host, uint16_t port) override {
        beast::error_code ec;

        // 解析域名
        auto results = resolver_.resolve(host, std::to_string(port), ec);
        if (ec) {
            std::cerr << "Resolve failed: " << ec.message() << std::endl;
            return false;
        }

        // 建立TCP连接
        auto endpoint = results.begin();
        beast::get_lowest_layer(ws_).connect(*endpoint, ec);
        if (ec) {
            std::cerr << "Connect failed: " << ec.message() << std::endl;
            return false;
        }

        // 升级到WebSocket协议
        ws_.handshake(host, "/", ec);
        if (ec) {
            std::cerr << "Handshake failed: " << ec.message() << std::endl;
            return false;
        }

        return true;
    }

    bool send(const std::string& message) override {
        beast::error_code ec;
        ws_.write(asio::buffer(message), ec);
        if (ec) {
            std::cerr << "Send failed: " << ec.message() << std::endl;
            return false;
        }
        return true;
    }

    std::string receive() override {
        beast::flat_buffer buffer;
        beast::error_code ec;
        ws_.read(buffer, ec);
        if (ec && ec != beast::websocket::error::closed) {
            std::cerr << "Receive failed: " << ec.message() << std::endl;
            return "";
        }
        return beast::buffers_to_string(buffer.data());
    }

    void disconnect() override {
        beast::error_code ec;
        ws_.close(beast::websocket::close_code::normal, ec);
        if (ec) {
            std::cerr << "Disconnect failed: " << ec.message() << std::endl;
        }
    }

private:
    boost::asio::ip::tcp::resolver resolver_;
    boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws_;
};
