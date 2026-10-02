#pragma once

#include <string>

#include "env/Environment.hpp"


namespace zoo::persistence {
    class JsonStore {
    public:
        static void save(const env::Environment &environment, const std::string &file);
        static void load(env::Environment &environment, const std::string &file);
    };
}