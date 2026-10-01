#pragma once

#include <vector>


namespace zoo::cli {
    class CommandParser {
    public:
        static std::vector<std::string> parse(const std::string &input);
    };
}
