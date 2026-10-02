#pragma once

#include "replxx.hxx"
#include "env/Environment.hpp"


namespace zoo::cli {
    class Cli {
    public:
        explicit Cli(env::Environment &environment) : environment_(environment) {
        }

        void run();

    protected:
        env::Environment &environment_;
        replxx::Replxx replxx_;

        void execute(const std::vector<std::string> &args) const;

        void route_env(const std::vector<std::string> &args) const;
        void route_zoo(const std::vector<std::string> &args) const;
        void route_animal(const std::vector<std::string> &args) const;

        void cmd_env_load(const std::vector<std::string> &args) const;
        void cmd_env_save(const std::vector<std::string> &args) const;
        void cmd_env_flush(const std::vector<std::string> &args) const;

        void cmd_zoo_list(const std::vector<std::string> &args) const;
        void cmd_zoo_add(const std::vector<std::string> &args) const;
        void cmd_zoo_rm(const std::vector<std::string> &args) const;
        void cmd_zoo_rename(const std::vector<std::string> &args) const;
        void cmd_zoo_food(const std::vector<std::string> &args) const;
        void cmd_zoo_describe(const std::vector<std::string> &args) const;

        void cmd_animal_list(const std::vector<std::string> &args) const;
        void cmd_animal_add(const std::vector<std::string> &args) const;
        void cmd_animal_rm(const std::vector<std::string> &args) const;
        void cmd_animal_rename(const std::vector<std::string> &args) const;
        void cmd_animal_find(const std::vector<std::string> &args) const;
        void cmd_animal_move(const std::vector<std::string> &args) const;
        void cmd_animal_exchange(const std::vector<std::string> &args) const;

        void cmd_help() const;
        void cmd_credits() const;
        void show_error(const std::exception &exception) const;

        std::string describe_animal(const animal::Animal &animal, std::optional<int> idx = std::nullopt) const;
    };
}
