// ReSharper disable CppLocalVariableMayBeConst
#include "cli/Cli.hpp"

#include <iostream>

#include "animal/AnimalType.hpp"
#include "cli/CommandParser.hpp"
#include "exception/ZooException.hpp"
#include "persistence/JsonStore.hpp"


namespace zoo::cli {
    void Cli::run() {
        while (true) {
            const char *input = replxx_.input("zoo> ");
            if (input == nullptr) break;
            if (*input == '\0') continue;
            replxx_.history_add(input);
            try { execute(CommandParser::parse(input)); } catch (const std::exception &exception) { show_error(exception); }
        }
    }

    void Cli::execute(const std::vector<std::string> &args) const {
        if (args.empty()) return;
        if (args[0] == "help") {
            cmd_help();
        } else if (args[0] == "credits") {
            cmd_credits();
        } else if (args[0] == "env") {
            route_env(args);
        } else if (args[0] == "zoo") {
            route_zoo(args);
        } else if (args[0] == "animal") {
            route_animal(args);
        } else {
            throw exception::ZooException("Unknown command: " + args[0]);
        }
    }

    void Cli::route_env(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: env <load|save|flush>");
        const auto &command = args[1];
        if (command == "load") {
            cmd_env_load(args);
            return;
        }
        if (command == "save") {
            cmd_env_save(args);
            return;
        }
        if (command == "flush") {
            cmd_env_flush(args);
            return;
        }
        throw exception::ZooException(std::format("Unknown environment command: {}", command));
    }


    void Cli::route_zoo(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: zoo <command>");
        const auto &command = args[1];
        if (command == "list") {
            cmd_zoo_list(args);
            return;
        }
        if (command == "add") {
            cmd_zoo_add(args);
            return;
        }
        if (command == "rm") {
            cmd_zoo_rm(args);
            return;
        }
        if (command == "rename") {
            cmd_zoo_rename(args);
            return;
        }
        if (command == "food") {
            cmd_zoo_food(args);
            return;
        }
        if (command == "describe") {
            cmd_zoo_describe(args);
            return;
        }
        throw exception::ZooException(std::format("Unknown zoo command: {}", command));
    }


    void Cli::route_animal(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: animal <command>");
        const auto &command = args[1];
        if (command == "list") {
            cmd_animal_list(args);
            return;
        }
        if (command == "add") {
            cmd_animal_add(args);
            return;
        }
        if (command == "rm") {
            cmd_animal_rm(args);
            return;
        }
        if (command == "rename") {
            cmd_animal_rename(args);
            return;
        }
        if (command == "find") {
            cmd_animal_find(args);
            return;
        }
        if (command == "move") {
            cmd_animal_move(args);
            return;
        }
        if (command == "exchange") {
            cmd_animal_exchange(args);
            return;
        }
        throw exception::ZooException(std::format("Unknown animal command: {}", command));
    }

    void Cli::cmd_env_load(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: env load <filename>");
        persistence::JsonStore::load(environment_, args[2]);
        std::cout << "Environment loaded successfully.\n";
    }

    void Cli::cmd_env_save(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: env save <filename>");
        persistence::JsonStore::save(environment_, args[2]);
        std::cout << "Environment saved successfully.\n";
    }

    void Cli::cmd_env_flush(const std::vector<std::string> &args) const {
        if (args.size() != 2) throw exception::ZooException("Usage: env flush");
        environment_.clear();
        std::cout << "Environment cleared.\n";
    }

    void Cli::cmd_zoo_list(const std::vector<std::string> &args) const {
        if (args.size() != 2) throw exception::ZooException("Usage: zoo list");
        if (environment_.zoos().empty()) {
            std::cout << "No zoos.\n";
            return;
        }
        for (std::size_t i{0}; auto &&zoo: environment_.zoos()) {
            std::cout << (i + 1) << " - " << zoo->name() << '\n';
            i++;
        }
    }

    void Cli::cmd_zoo_add(const std::vector<std::string> &args) const {
        if (args.size() != 7 || args[3] != "--food" || args[5] != "--cages") throw exception::ZooException("Usage: zoo add <name> --food <food_reserve> --cages <count>");
        const int food = std::stoi(args[4]);
        const int cages = std::stoi(args[6]);
        environment_.add_zoo(args[2], food, cages);
        std::cout << "Zoo added successfully.\n";
    }

    void Cli::cmd_zoo_rm(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: zoo rm <name>");
        environment_.remove_zoo(args[2]);
        std::cout << "Zoo removed successfully.\n";
    }

    void Cli::cmd_zoo_rename(const std::vector<std::string> &args) const {
        if (args.size() != 4) throw exception::ZooException("Usage: zoo rename <name> <new_name>");
        zoo::Zoo &zoo = environment_.zoo(args[2]);
        zoo.set_name(args[3]);
        std::cout << "Zoo renamed successfully.\n";
    }

    void Cli::cmd_zoo_food(const std::vector<std::string> &args) const {
        if (args.size() < 3) throw exception::ZooException("Usage: zoo food <add|rm> <name> <qty>");
        if (args.size() != 5) throw exception::ZooException("Usage: zoo food <add|rm> <name> <qty>");
        zoo::Zoo &zoo = environment_.zoo(args[3]);
        const std::string &food_command = args[2];
        const int amount = std::stoi(args[4]);
        if (food_command == "add") {
            zoo.add_food_reserve(amount);
        } else if (food_command == "rm") {
            zoo.remove_food_reserve(amount);
        } else throw exception::ZooException(std::format("Unknown food command: {}", food_command));
        std::cout << "Food reserve updated successfully.\n";
    }

    void Cli::cmd_zoo_describe(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: zoo describe <name>");
        std::cout << environment_.zoo(args[2]).describe() << '\n';
    }

    void Cli::cmd_animal_list(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: animal list <zoo>");
        const zoo::Zoo &zoo = environment_.zoo(args[2]);
        bool found = false;
        for (std::size_t i{0}; auto &&animal: zoo.animals()) {
            if (animal == nullptr) continue;
            found = true;
            std::cout << describe_animal(*animal, i);
            i++;
        }
        if (!found) std::cout << "No animals.\n";
    }

    void Cli::cmd_animal_add(const std::vector<std::string> &args) const {
        if (args.size() != 8) throw exception::ZooException("Usage: animal add <zoo> <name> <type> <age> <food_per_day> <cage>");
        zoo::Zoo &zoo = environment_.zoo(args[2]);
        const animal::AnimalType type = animal::animal_type_from_string(args[4]);
        const int age = std::stoi(args[5]);
        const int food_per_day = std::stoi(args[6]);
        const int cage = std::stoi(args[7]);
        zoo.add_animal(args[3], type, age, food_per_day, cage);
        std::cout << "Animal added successfully.\n";
    }

    void Cli::cmd_animal_rm(const std::vector<std::string> &args) const {
        if (args.size() != 4) throw exception::ZooException("Usage: animal rm <zoo> <name>");
        environment_.zoo(args[2]).remove_animal(args[3]);
        std::cout << "Animal removed successfully.\n";
    }

    void Cli::cmd_animal_rename(const std::vector<std::string> &args) const {
        if (args.size() != 5) throw exception::ZooException("Usage: animal rename <zoo> <name> <new_name>");
        environment_.zoo(args[2]).rename_animal(args[3], args[4]);
        std::cout << "Animal renamed successfully.\n";
    }

    void Cli::cmd_animal_find(const std::vector<std::string> &args) const {
        if (args.size() != 3) throw exception::ZooException("Usage: animal find <query>");
        bool found = false;
        int i = 0;
        for (const auto &zoo: environment_.zoos()) {
            for (const std::vector<const animal::Animal *> animals = zoo->find(args[2]); auto *animal: animals) {
                found = true;
                std::cout << describe_animal(*animal, i);
                i++;
            }
        }
        if (!found) std::cout << "No animals found.\n";
    }

    void Cli::cmd_animal_move(const std::vector<std::string> &args) const {
        if (args.size() != 5 && args.size() != 6) throw exception::ZooException("Usage: animal move <zoo> <animal> <cage> [--swap]");
        const bool swap = args.size() == 6;
        if (swap && args[5] != "--swap") throw exception::ZooException("Usage: animal move <zoo> <animal> <cage> [--swap]");
        zoo::Zoo &zoo = environment_.zoo(args[2]);
        zoo.move(args[3], std::stoi(args[4]), swap);
        std::cout << "Animal moved successfully.\n";
    }

    void Cli::cmd_animal_exchange(const std::vector<std::string> &args) const {
        if (args.size() != 5 && args.size() != 7) throw exception::ZooException("Usage: animal exchange <zoo> <animal> <destination> [--swap-with <type>]");
        std::optional<animal::AnimalType> exchange_request;
        if (args.size() == 7) {
            if (args[5] != "--swap-with") throw exception::ZooException("Usage: animal exchange <zoo> <animal> <destination> [--swap-with <type>]");
            exchange_request = animal::animal_type_from_string(args[6]);
        }
        zoo::Zoo &source = environment_.zoo(args[2]);
        zoo::Zoo &destination = environment_.zoo(args[4]);
        source.exchange(args[3], destination, exchange_request);
        std::cout << "Animal exchange completed successfully.\n";
    }

    void Cli::cmd_help() const {
        std::cout
                << "ZooCLI - Zoo Management System\n"

                << "General\n"
                << "  help                                      Show this help dialog.\n"
                << "  credits                                   Show application credits.\n\n"

                << "Environment\n"
                << "  env load <filename>                       Load state from a JSON file.\n"
                << "  env save <filename>                       Save current state to a JSON file.\n"
                << "  env flush                                 Clear all zoos and animals.\n\n"

                << "Zoo\n"
                << "  zoo add <name> --food <reserve> --cages <count>\n"
                << "                                            Add a new zoo.\n"
                << "  zoo rm <name>                             Remove a zoo.\n"
                << "  zoo rename <name> <new_name>              Rename a zoo.\n"
                << "  zoo food add <name> <qty>                 Add food to a zoo's reserve.\n"
                << "  zoo food rm <name> <qty>                  Remove food from a zoo's reserve.\n"
                << "  zoo describe <name>                       Show zoo statistics.\n"
                << "  zoo list                                  List all zoos.\n\n"

                << "Animals\n"
                << "  animal add <zoo> <name> <type> <age> <food> <cage>\n"
                << "                                            Add an animal to a zoo.\n"
                << "  animal rm <zoo> <name>                    Remove an animal.\n"
                << "  animal rename <zoo> <name> <new_name>     Rename an animal.\n"
                << "  animal find <query>                       Find animals by name or type.\n"
                << "  animal move <zoo> <animal> <cage> [--swap]\n"
                << "                                            Move an animal to another cage.\n"
                << "  animal exchange <zoo> <animal> <destination> [--swap-with <type>]\n"
                << "                                            Transfer or exchange an animal.\n"
                << "  animal list <zoo>                         List all animals in a zoo.\n\n"

                << "Type 'help' at any time to display this dialog.\n";
    }

    void Cli::cmd_credits() const {
        std::cout << "ZooCLI - Zoo Management System\n\nCreated as a C++20 OOP project.\nUses replxx for the interactive command line.\nUses nlohmann/json for persistence.\n\n";
    }

    void Cli::show_error(const std::exception &exception) const {
        std::cerr << "Error: " << exception.what() << '\n';
    }

    std::string Cli::describe_animal(const animal::Animal &animal, const std::optional<int> idx) const {
        return std::format("{} - {} (Type: {}, Age: {}, Food/Day: {} kg, Cage: {})\n", idx.value_or(-1) + 1, animal.name(), animal_type_to_string(animal.type()), animal.age(), animal.daily_food_requirement(), animal.cage_id());
    }
}
