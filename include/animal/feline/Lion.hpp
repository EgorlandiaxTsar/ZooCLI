#pragma once

#include "animal/AnimalType.hpp"
#include "animal/feline/Feline.hpp"


namespace zoo::animal::feline {
    class Lion final : public Feline {
    public:
        using Feline::Feline;

        std::string sound() const override { return "Roar!"; }

        std::string description() const override { return "A powerful social big cat."; }

        AnimalType type() const override { return AnimalType::Lion; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
