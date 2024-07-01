#pragma once
#include <memory>
#include <future>
#include <string>
#include <functional>
#include <stdexcept>

#include "protocol.hpp"
#include "websocket_impl.hpp"
#include "protocol_factory.hpp"

class Client {
private:
    std::unique_ptr<Protocol> protocol_;

public:
    explicit Client(const std::string& protocolType, const std::string& host, uint16_t port) {
        protocol_ = ProtocolFactory::createProtocol(protocolType);
        if (!protocol_->connect(host, port)) {
            throw std::runtime_error("Failed to connect.");
        }
    }

    void sendMessage(const std::string& message) {
        if (!protocol_->send(message)) {
            std::cerr << "Failed to send message." << std::endl;
        }
    }

    std::string receiveMessage() {
        return protocol_->receive();
    }

    void disconnect() {
        protocol_->disconnect();
    }
};
