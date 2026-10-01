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
            try { execute(CommandParser::parse(input)); } catch (const std::exception &exception) { print_error(exception); }
        }
    }

    void Cli::execute(const std::vector<std::string> &args) const {
        if (args.empty()) return;
        if (args[0] == "help") {
            print_help();
        } else if (args[0] == "credits") {
            print_credits();
        } else if (args[0] == "env") {
            execute_env(args);
        } else if (args[0] == "zoo") {
            execute_zoo(args);
        } else if (args[0] == "animal") {
            execute_animal(args);
        } else {
            throw exception::ZooException("Unknown command: " + args[0]);
        }
    }

    void Cli::print_help() const {
        std::cout << "ZooCLI commands:\n" "\n" "General:\n" " help\n" " Print this help dialog.\n" " credits\n" " Print application credits.\n" "\n" "Environment:\n" " env load <filename>\n" " Load state from a JSON file.\n" " env save <filename>\n" " Save current state to a JSON file.\n" " env flush\n" " Remove all zoos and animals from the current state.\n" "\n" "Zoo:\n" " zoo add <name> --food <food_reserve> --cages <count>\n" " Add a new zoo.\n" " zoo rm <name>\n" " Remove a zoo.\n" " zoo rename <name> <new_name>\n" " Rename a zoo.\n" " zoo food add <name> <qty>\n" " Add food to a zoo's reserve.\n" " zoo food rm <name> <qty>\n" " Remove food from a zoo's reserve.\n" " zoo describe <name>\n" " Print zoo statistics.\n" " zoo list\n" " List all zoos.\n" "\n" "Animals:\n" " animal add <zoo> <name> <type> <age> <food_per_day> <cage>\n" " Add an animal to a zoo.\n" " animal rm <zoo> <name>\n" " Remove an animal.\n" " animal rename <zoo> <name> <new_name>\n" " Rename an animal.\n" " animal find <query>\n" " Find animals by name or type.\n" " animal move <zoo> <animal> <cage> [--swap]\n" " Move an animal to another cage.\n" " animal exchange <zoo> <animal> <destination> [--swap-with <type>]\n" " Transfer or exchange an animal with another zoo.\n" " animal list <zoo>\n" " List all animals in a zoo.\n" "\n";
    }

    void Cli::print_credits() const {
        std::cout << "ZooCLI\n" "Zoo Management System\n" "\n" "Created as a C++20 OOP project.\n" "Uses replxx for the interactive command line.\n" "Uses nlohmann/json for persistence.\n" "\n";
    }

    void Cli::execute_env(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: env <load|save|flush>");
        const auto &command = args[1];
        if (command == "load") {
            if (args.size() != 3) throw exception::ZooException("Usage: env load <filename>");
            persistence::JsonStore::load(environment_, args[2]);
            std::cout << "Environment loaded successfully.\n";
            return;
        }
        if (command == "save") {
            if (args.size() != 3) throw exception::ZooException("Usage: env save <filename>");
            persistence::JsonStore::save(environment_, args[2]);
            std::cout << "Environment saved successfully.\n";
            return;
        }
        if (command == "flush") {
            if (args.size() != 2) throw exception::ZooException("Usage: env flush");
            environment_.clear();
            std::cout << "Environment cleared.\n";
            return;
        }
        throw exception::ZooException(std::format("Unknown environment command: {}", command));
    }


    void Cli::execute_zoo(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: zoo <command>");
        const auto &command = args[1];
        if (command == "list") {
            if (args.size() != 2) throw exception::ZooException("Usage: zoo list");
            if (environment_.zoos().empty()) {
                std::cout << "No zoos.\n";
                return;
            }
            for (const auto &zoo: environment_.zoos()) std::cout << zoo->name() << '\n';
            return;
        }
        if (command == "add") {
            if (args.size() != 7 ||
                args[3] != "--food" ||
                args[5] != "--cages") {
                throw exception::ZooException("Usage: zoo add <name> --food <food_reserve> --cages <count>");
            }
            const int food = std::stoi(args[4]);
            const int cages = std::stoi(args[6]);
            environment_.add_zoo(args[2], food, cages);
            std::cout << "Zoo added successfully.\n";
            return;
        }
        if (command == "rm") {
            if (args.size() != 3) throw exception::ZooException("Usage: zoo rm <name>");
            environment_.remove_zoo(args[2]);
            std::cout << "Zoo removed successfully.\n";
            return;
        }
        if (command == "rename") {
            if (args.size() != 4) throw exception::ZooException("Usage: zoo rename <name> <new_name>");
            auto &zoo = environment_.zoo(args[2]);
            zoo.set_name(args[3]);
            std::cout << "Zoo renamed successfully.\n";
            return;
        }
        if (command == "food") {
            if (args.size() < 3) throw exception::ZooException("Usage: zoo food <add|rm> <name> <qty>");
            const auto &food_command = args[2];
            if (args.size() != 5) throw exception::ZooException("Usage: zoo food <add|rm> <name> <qty>");
            auto &zoo = environment_.zoo(args[3]);
            const int amount = std::stoi(args[4]);
            if (food_command == "add") {
                zoo.add_food_reserve(amount);
            } else if (food_command == "rm") {
                zoo.remove_food_reserve(amount);
            } else {
                throw exception::ZooException(std::format("Unknown food command: {}", food_command));
            }
            std::cout << "Food reserve updated successfully.\n";
            return;
        }
        if (command == "describe") {
            if (args.size() != 3) throw exception::ZooException("Usage: zoo describe <name>");
            std::cout << environment_.zoo(args[2]).describe() << '\n';
            return;
        }
        throw exception::ZooException(std::format("Unknown zoo command: {}", command));
    }


    void Cli::execute_animal(const std::vector<std::string> &args) const {
        if (args.size() < 2) throw exception::ZooException("Usage: animal <command>");
        const auto &command = args[1];
        if (command == "add") {
            if (args.size() != 8) throw exception::ZooException("Usage: animal add <zoo> <name> <type> <age> <food_per_day> <cage>");
            auto &zoo = environment_.zoo(args[2]);
            const auto type = animal::animal_type_from_string(args[4]);
            const int age = std::stoi(args[5]);
            const int food_per_day = std::stoi(args[6]);
            const int cage = std::stoi(args[7]);
            zoo.add_animal(args[3], type, age, food_per_day, cage);
            std::cout << "Animal added successfully.\n";
            return;
        }
        if (command == "rm") {
            if (args.size() != 4) throw exception::ZooException("Usage: animal rm <zoo> <name>");
            environment_.zoo(args[2]).remove_animal(args[3]);
            std::cout << "Animal removed successfully.\n";
            return;
        }
        if (command == "rename") {
            if (args.size() != 5) throw exception::ZooException("Usage: animal rename <zoo> <name> <new_name>");
            environment_.zoo(args[2]).rename_animal(args[3], args[4]);
            std::cout << "Animal renamed successfully.\n";
            return;
        }
        if (command == "find") {
            if (args.size() != 3) throw exception::ZooException("Usage: animal find <query>");
            bool found = false;
            for (const auto &zoo: environment_.zoos()) {
                for (const auto animals = zoo->find(args[2]); const auto *animal: animals) {
                    found = true;
                    std::cout << zoo->name() << ": " << animal->name() << " (" << animal_type_to_string(animal->type()) << ", age " << animal->age() << ", cage " << animal->cage_id() << ")\n";
                }
            }
            if (!found) std::cout << "No animals found.\n";
            return;
        }
        if (command == "move") {
            if (args.size() != 5 && args.size() != 6) throw exception::ZooException("Usage: animal move <zoo> <animal> <cage> [--swap]");
            const bool swap = args.size() == 6;
            if (swap && args[5] != "--swap") throw exception::ZooException("Usage: animal move <zoo> <animal> <cage> [--swap]");
            auto &zoo = environment_.zoo(args[2]);
            zoo.move(args[3], std::stoi(args[4]), swap);
            std::cout << "Animal moved successfully.\n";
            return;
        }
        if (command == "exchange") {
            if (args.size() != 5 && args.size() != 7) {
                throw exception::ZooException(
                    "Usage: animal exchange <zoo> <animal> <destination> [--swap-with <type>]"
                );
            }

            std::optional<animal::AnimalType> exchange_request;

            if (args.size() == 7) {
                if (args[5] != "--swap-with") {
                    throw exception::ZooException(
                        "Usage: animal exchange <zoo> <animal> <destination> [--swap-with <type>]"
                    );
                }

                exchange_request = animal::animal_type_from_string(args[6]);
            }

            auto &source = environment_.zoo(args[2]);
            auto &destination = environment_.zoo(args[4]);

            source.exchange(args[3], destination, exchange_request);

            std::cout << "Animal exchange completed successfully.\n";
            return;
        }
        if (command == "list") {
            if (args.size() != 3) throw exception::ZooException("Usage: animal list <zoo>");
            const auto &zoo = environment_.zoo(args[2]);
            bool found = false;
            for (const auto &animal: zoo.animals()) {
                if (animal == nullptr) continue;
                found = true;
                std::cout << animal->name() << " | " << animal_type_to_string(animal->type()) << " | age: " << animal->age() << " | food/day: " << animal->daily_food_requirement() << " kg" << " | cage: " << animal->cage_id() << '\n';
            }
            if (!found) std::cout << "No animals.\n";
            return;
        }
        throw exception::ZooException(std::format("Unknown animal command: {}", command));
    }

    void Cli::print_error(const std::exception &exception) const {
        std::cerr << "Error: " << exception.what() << '\n';
    }
}
