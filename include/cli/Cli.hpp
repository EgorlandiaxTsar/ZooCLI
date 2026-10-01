#pragma once

#include "replxx.hxx"
#include "env/Environment.hpp"


namespace zoo::cli {
    class Cli {
    public:
        explicit Cli(env::Environment &environment) : environment_(environment) {
        }

        void run();

    private:
        env::Environment &environment_;
        replxx::Replxx replxx_;

        void execute(const std::vector<std::string> &args) const;

        void print_help() const;

        void print_credits() const;

        void execute_env(const std::vector<std::string> &args) const;

        void execute_zoo(const std::vector<std::string> &args) const;

        void execute_animal(const std::vector<std::string> &args) const;

        void print_error(const std::exception &exception) const;
    };
}
