#pragma once

#include "animal/AnimalType.hpp"
#include "animal/feline/Feline.hpp"


namespace zoo::animal::feline {
    class Tiger final : public Feline {
    public:
        using Feline::Feline;

        std::string sound() const override { return "Roar!"; }

        std::string description() const override { return "A large striped wild cat."; }

        AnimalType type() const override { return AnimalType::Tiger; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
