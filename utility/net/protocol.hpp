#pragma once
#include <string>
class Protocol {
public:
    virtual ~Protocol() = default;
    virtual bool connect(const std::string& host, uint16_t port) = 0;
    virtual bool send(const std::string& message) = 0;
    virtual std::string receive() = 0;
    virtual void disconnect() = 0;
};