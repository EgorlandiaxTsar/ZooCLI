#include "zoo/Zoo.hpp"

#include <numeric>

#include "animal/canine/ArcticFox.hpp"
#include "animal/canine/Dhole.hpp"
#include "animal/canine/RedFox.hpp"
#include "animal/canine/Wolf.hpp"
#include "animal/feline/Cheetah.hpp"
#include "animal/feline/Jaguar.hpp"
#include "animal/feline/Lion.hpp"
#include "animal/feline/Tiger.hpp"
#include "animal/marsupial/Kangaroo.hpp"
#include "animal/marsupial/Koala.hpp"
#include "animal/marsupial/TasmanianDevil.hpp"
#include "animal/marsupial/Wombat.hpp"
#include "animal/reptile/Alligator.hpp"
#include "animal/reptile/Crocodile.hpp"
#include "animal/reptile/Iguana.hpp"
#include "animal/reptile/KomodoDragon.hpp"
#include "exception/ZooException.hpp"


namespace zoo::zoo {
    void Zoo::add_food_reserve(const int amount) { food_reserve_ += amount; }

    void Zoo::remove_food_reserve(const int amount) {
        if (food_reserve_ - amount < 0) throw exception::ZooException("Cannot remove more than the current food amount");
        food_reserve_ -= amount;
    }

    std::string Zoo::describe() const {
        int food_per_day = std::accumulate(std::ranges::begin(animals_), std::ranges::end(animals_), 0, [](int sum, const std::unique_ptr<animal::Animal> &animal) {
            return sum + (animal == nullptr ? 0 : animal.get()->daily_food_requirement());
        });
        return std::format(
            "Zoo: {}\n"
            "Food reserve: {} kg\n"
            "Cages: {}/{}\n"
            "Daily food consumption: {} kg\n"
            "Monthly food consumption: {} kg",
            name_,
            food_reserve_,
            cages_occupied_,
            cages_count_,
            food_per_day,
            food_per_day * 30
        );
    }

    void Zoo::add_animal(const std::string &name, animal::AnimalType type, const int age, const int food_per_day, const int cage) {
        if (name.empty()) throw exception::ZooException("Name cannot be empty");
        if (food_per_day < 0) throw exception::ZooException("Food consumption per day must be greater than 0");
        if (cage < 0 or cage >= cages_count_) throw exception::ZooException("Cage ID is out of range");
        if (animals_[cage] != nullptr) throw exception::ZooException("Cage is already occupied");
        if (find_animal_by_name(name) != nullptr) throw exception::ZooException("This animal already exists");
        std::unique_ptr<animal::Animal> new_animal;
        switch (type) {
            case animal::AnimalType::Tiger:
                new_animal = std::make_unique<animal::feline::Tiger>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Lion:
                new_animal = std::make_unique<animal::feline::Lion>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Cheetah:
                new_animal = std::make_unique<animal::feline::Cheetah>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Jaguar:
                new_animal = std::make_unique<animal::feline::Jaguar>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Crocodile:
                new_animal = std::make_unique<animal::reptile::Crocodile>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Alligator:
                new_animal = std::make_unique<animal::reptile::Alligator>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::KomodoDragon:
                new_animal = std::make_unique<animal::reptile::KomodoDragon>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Iguana:
                new_animal = std::make_unique<animal::reptile::Iguana>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Kangaroo:
                new_animal = std::make_unique<animal::marsupial::Kangaroo>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Koala:
                new_animal = std::make_unique<animal::marsupial::Koala>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Wombat:
                new_animal = std::make_unique<animal::marsupial::Wombat>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::TasmanianDevil:
                new_animal = std::make_unique<animal::marsupial::TasmanianDevil>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Wolf:
                new_animal = std::make_unique<animal::canine::Wolf>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::RedFox:
                new_animal = std::make_unique<animal::canine::RedFox>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::ArcticFox:
                new_animal = std::make_unique<animal::canine::ArcticFox>(name, age, food_per_day, cage);
                break;

            case animal::AnimalType::Dhole:
                new_animal = std::make_unique<animal::canine::Dhole>(name, age, food_per_day, cage);
                break;
        }
        animals_[cage] = std::move(new_animal);
        cages_occupied_++;
    }

    void Zoo::remove_animal(const std::string &name) {
        find_slot_by_name(name, true)->reset();
        cages_occupied_--;
    }

    void Zoo::rename_animal(const std::string &name, const std::string &new_name) {
        find_animal_by_name(name, true)->set_name(new_name);
    }

    std::vector<const animal::Animal *> Zoo::find(const std::string &query) const {
        std::vector<const animal::Animal *> result;
        std::string normalized_query = query;
        std::ranges::transform(normalized_query, normalized_query.begin(), [](const unsigned char character) {
            return static_cast<char>(std::tolower(character));
        });
        for (const auto &animal: animals_) {
            if (animal == nullptr) continue;
            std::string name = animal->name();
            std::string type = animal_type_to_string(animal->type());
            std::ranges::transform(name, name.begin(), [](const unsigned char character) {
                return static_cast<char>(std::tolower(character));
            });
            std::ranges::transform(type, type.begin(), [](const unsigned char character) {
                return static_cast<char>(std::tolower(character));
            });
            if (name.find(normalized_query) != std::string::npos || type.find(normalized_query) != std::string::npos) result.push_back(animal.get());
        }
        return result;
    }

    void Zoo::move(const std::string &name, const int cage, const bool swap) {
        if (cage < 0 or cage >= cages_count_) throw exception::ZooException("Cage ID is out of range");
        const auto target = find_slot_by_name(name);
        const int target_idx = target - animals_.begin();
        if (cage == target_idx) throw exception::ZooException("Cannot move animal to the same cage");
        if (animals_[cage] != nullptr) {
            if (!swap) throw exception::ZooException("Cage is already occupied, use --swap to swap animals");
            (*target)->set_cage_id(cage);
            animals_[cage]->set_cage_id(target_idx);
            std::swap(*target, animals_[cage]);
        } else {
            animals_[cage] = std::move(*target);
            animals_[cage]->set_cage_id(cage);
        }
    }

    void Zoo::exchange(const std::string &name, Zoo &destination, std::optional<animal::AnimalType> exchange_request) {
        const auto slot = find_slot_by_name(name, true);
        destination.internal_exchange(*this, std::move(*slot), slot - animals_.begin(), exchange_request);
        if (exchange_request == std::nullopt) cages_occupied_--;
    }

    animal::Animal *Zoo::find_animal_by_name(const std::string &name, const bool destructive) {
        const auto iter = find_slot_by_name(name, destructive);
        if (iter == animals_.end()) return nullptr;
        return iter->get();
    }

    std::unique_ptr<animal::Animal> Zoo::extract_animal_by_name(const std::string &name, const bool destructive) {
        const auto iter = find_slot_by_name(name, destructive);
        if (iter == animals_.end()) return nullptr;
        return std::move(*iter);
    }

    std::vector<std::unique_ptr<animal::Animal> >::iterator Zoo::find_slot_by_name(const std::string &name, const bool destructive) {
        const auto slot = std::ranges::find_if(animals_, [&](const auto &animal_ptr) {
            return animal_ptr != nullptr && animal_ptr->name() == name;
        });
        if (slot == animals_.end() && destructive) throw exception::ZooException("Animal not found");
        return slot;
    }

    void Zoo::internal_exchange(Zoo &caller, std::unique_ptr<animal::Animal> animal, const int animal_cage, const std::optional<animal::AnimalType> exchange_request) {
        try {
            if (cages_occupied_ == cages_count_) throw exception::ZooException("Destination zoo cannot host new animal since it reached it's max capacity");
            if (find_animal_by_name(animal.get()->name()) != nullptr) throw exception::ZooException(std::format("Animal {} already exists in zoo {}", animal.get()->name(), this->name()));
            if (exchange_request != std::nullopt) {
                if (!has_any_animal(exchange_request.value())) throw exception::ZooException("Cannot find any animal of the desired type");
                const auto exchange_animal_slot = first_animal_slot_by_type(exchange_request.value());
                caller.internal_exchange(*this, std::move(*exchange_animal_slot), exchange_animal_slot - animals_.begin());
                cages_occupied_--;
            }
            animals_[first_free_cage()] = std::move(animal);
            cages_occupied_++;
        } catch ([[maybe_unused]] exception::ZooException &ex) {
            // Revert on failure
            caller.animals_[animal_cage] = std::move(animal);
            caller.cages_occupied_++;
            throw;
        }
    }

    int Zoo::first_free_cage() {
        const auto iter = std::ranges::find(animals_, nullptr);
        if (iter == animals_.end()) throw exception::ZooException("The zoo is full");
        return iter - animals_.begin();
    }

    std::vector<std::unique_ptr<animal::Animal> >::iterator Zoo::first_animal_slot_by_type(animal::AnimalType type) {
        const auto slot = std::ranges::find_if(animals_, [&](const auto &animal_ptr) {
            return animal_ptr != nullptr && animal_ptr->type() == type;
        });
        if (slot == animals_.end()) throw exception::ZooException("Cannot find any animal of the desired type");
        return slot;
    }

    bool Zoo::has_any_animal(animal::AnimalType type) {
        const auto slot = std::ranges::find_if(animals_, [&](const auto &animal_ptr) {
            return animal_ptr != nullptr && animal_ptr->type() == type;
        });
        return slot != animals_.end();
    }
}
