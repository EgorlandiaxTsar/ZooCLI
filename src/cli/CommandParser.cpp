#include "cli/CommandParser.hpp"

#include <sstream>


namespace zoo::cli {
    std::vector<std::string> CommandParser::parse(const std::string &input) {
        std::istringstream stream(input);
        std::vector<std::string> result;
        std::string token;
        while (stream >> token) result.push_back(token);
        return result;
    }
}
