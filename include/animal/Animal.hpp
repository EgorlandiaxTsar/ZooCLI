#pragma once

#include <string>


namespace zoo::animal {
    enum class AnimalType;
    enum class AnimalFoodType;

    class Animal {
    public:
        virtual ~Animal() = default;

        Animal(
            const std::string &name,
            const int age,
            const int daily_food_requirement,
            const int cage_id
        ) : name_(name),
            age_(age),
            daily_food_requirement_(daily_food_requirement),
            cage_id_(cage_id) {
        }

        virtual std::string sound() const = 0;

        virtual std::string description() const = 0;

        virtual AnimalType type() const = 0;

        virtual AnimalFoodType food_type() const = 0;

        const std::string &name() const { return name_; }
        int age() const { return age_; }
        int daily_food_requirement() const { return daily_food_requirement_; }
        int cage_id() const { return cage_id_; }

        void set_name(const std::string &name) { name_ = name; }
        void set_age(const int age) { age_ = age; }
        void set_daily_food_requirement(const int daily_food_requirement) { daily_food_requirement_ = daily_food_requirement; }
        void set_cage_id(const int cage_id) { cage_id_ = cage_id; }

    protected:
        std::string name_;
        int age_;
        int daily_food_requirement_;
        int cage_id_;
    };
}
