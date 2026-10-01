#pragma once

#include <string>
#include <vector>

#include "animal/Animal.hpp"


namespace zoo::zoo {
    class Zoo {
    public:
        Zoo(
            const std::string &name,
            const int food_reserve,
            const int cages_count
        ) : name_(name),
            food_reserve_(food_reserve),
            cages_count_(cages_count),
            cages_occupied_(0),
            animals_(cages_count) {
        }

        void add_food_reserve(int amount);

        void remove_food_reserve(int amount);

        std::string describe() const;

        void add_animal(const std::string &name, animal::AnimalType type, int age, int food_per_day, int cage);

        void remove_animal(const std::string &name);

        void rename_animal(const std::string &name, const std::string &new_name);

        std::vector<const animal::Animal *> find(const std::string &query) const;

        void move(const std::string &name, int cage, bool swap = false);

        void exchange(const std::string &name, Zoo &destination, std::optional<animal::AnimalType> exchange_request = std::nullopt);

        const std::string &name() const { return name_; }
        const std::vector<std::unique_ptr<animal::Animal> > &animals() const { return animals_; }
        int food_reserve() const { return food_reserve_; }
        int cages_count() const { return cages_count_; }
        int cages_occupied() const { return cages_occupied_; }

        void set_name(const std::string &name) { name_ = name; }

    protected:
        std::string name_;
        int food_reserve_;
        int cages_count_;
        int cages_occupied_;
        std::vector<std::unique_ptr<animal::Animal> > animals_;

        animal::Animal *find_animal_by_name(const std::string &name, bool destructive = false);

        std::unique_ptr<animal::Animal> extract_animal_by_name(const std::string &name, bool destructive = false);

        std::vector<std::unique_ptr<animal::Animal> >::iterator find_slot_by_name(const std::string &name, bool destructive = false);

        void internal_exchange(Zoo &caller, std::unique_ptr<animal::Animal> animal, int animal_cage, std::optional<animal::AnimalType> exchange_request = std::nullopt);

        int first_free_cage();

        std::vector<std::unique_ptr<animal::Animal> >::iterator first_animal_slot_by_type(animal::AnimalType type);

        bool has_any_animal(animal::AnimalType type);
    };
}
