#pragma once

#include <exception>
#include <format>


namespace zoo::exception {
    class ZooException : public std::exception {
    public:
        explicit ZooException(const std::string &message = "no description") : message_("ZooException occurred: " + message) {
        }

        const char *what() const noexcept override { return message_.c_str(); }

    private:
        std::string message_;
    };
}
