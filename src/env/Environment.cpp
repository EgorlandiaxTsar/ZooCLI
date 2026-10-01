#include "env/Environment.hpp"

#include "exception/ZooException.hpp"


namespace zoo::env {
    void Environment::add_zoo(const std::string &name, int food_reserve, int cages_count) {
        if (name.empty()) throw exception::ZooException("Name cannot be empty");
        if (food_reserve < 0) throw exception::ZooException("Food reserve must be greater or equal to zero");
        if (cages_count <= 0) throw exception::ZooException("Zoo must have at least one cage");
        if (find_zoo_by_name(name) != nullptr) throw exception::ZooException("This zoo already exists");
        zoos_.emplace_back(std::make_unique<zoo::Zoo>(name, food_reserve, cages_count));
    }

    void Environment::remove_zoo(const std::string &name) {
        zoos_.erase(find_slot_by_name(name, true));
    }

    zoo::Zoo &Environment::zoo(const std::string &name) {
        return *find_zoo_by_name(name, true);
    }

    void Environment::clear() { zoos_.clear(); }

    zoo::Zoo *Environment::find_zoo_by_name(const std::string &name, const bool destructive) {
        const auto iter = find_slot_by_name(name, destructive);
        if (iter == zoos_.end()) return nullptr;
        return iter->get();
    }

    std::vector<std::unique_ptr<zoo::Zoo> >::iterator Environment::find_slot_by_name(const std::string &name, const bool destructive) {
        const auto slot = std::ranges::find_if(zoos_, [&](const auto &animal_ptr) {
            return animal_ptr != nullptr && animal_ptr->name() == name;
        });
        if (slot == zoos_.end() && destructive) throw exception::ZooException("Zoo not found");
        return slot;
    }
}
