#pragma once
#include "protocol.hpp"
#include "websocket_impl.hpp"
#include <string>

class ProtocolFactory {
public:
    static std::unique_ptr<Protocol> createProtocol(const std::string& protocolType) {
        static boost::asio::io_context ioc;
        if (protocolType == "WebSocket") {
            std::cout << protocolType << std::endl;
            return std::make_unique<WebSocketImpl>(ioc);
        }else {
            return nullptr;
        }
    }
};