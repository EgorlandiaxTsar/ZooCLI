#include "persistence/JsonStore.hpp"

#include <fstream>
#include <iomanip>
#include <nlohmann/json.hpp>

#include "animal/AnimalType.hpp"
#include "exception/ZooException.hpp"


namespace zoo::persistence {
    using json = nlohmann::json;

    void JsonStore::save(const env::Environment &environment, const std::string &file) {
        json root;
        root["zoos"] = json::array();
        for (const auto &zoo_ptr: environment.zoos()) {
            const auto &zoo = *zoo_ptr;
            json zoo_json;
            zoo_json["name"] = zoo.name();
            zoo_json["food_reserve"] = zoo.food_reserve();
            zoo_json["cages_count"] = zoo.cages_count();
            zoo_json["animals"] = json::array();
            for (const auto &animal_ptr: zoo.animals()) {
                if (animal_ptr == nullptr) continue;
                const auto &animal = *animal_ptr;
                zoo_json["animals"].push_back({
                    {"name", animal.name()},
                    {"type", animal::animal_type_to_string(animal.type())},
                    {"age", animal.age()},
                    {"food_per_day", animal.daily_food_requirement()},
                    {"cage", animal.cage_id()}
                });
            }
            root["zoos"].push_back(std::move(zoo_json));
        }
        std::ofstream output(file);
        if (!output) throw exception::ZooException("Cannot open file for writing");
        output << std::setw(4) << root;
        if (!output) throw exception::ZooException("Failed to write file");
    }

    void JsonStore::load(env::Environment &environment, const std::string &file) {
        std::ifstream input(file);
        if (!input) throw exception::ZooException("Cannot open file for reading");
        json root;
        try { input >> root; } catch (const json::parse_error &) { throw exception::ZooException("Invalid JSON file"); }
        environment.clear();
        for (const auto &zoo_json: root.at("zoos")) {
            const auto name = zoo_json.at("name").get<std::string>();
            const auto food_reserve = zoo_json.at("food_reserve").get<int>();
            const auto cages_count = zoo_json.at("cages_count").get<int>();
            environment.add_zoo(name, food_reserve, cages_count);
            auto &zoo = environment.zoo(name);
            for (const auto &animal_json: zoo_json.at("animals")) {
                zoo.add_animal(
                    animal_json.at("name").get<std::string>(),
                    animal::animal_type_from_string(animal_json.at("type").get<std::string>()),
                    animal_json.at("age").get<int>(),
                    animal_json.at("food_per_day").get<int>(),
                    animal_json.at("cage").get<int>()
                );
            }
        }
    }
}
