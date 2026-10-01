#pragma once

#include "animal/AnimalType.hpp"
#include "animal/feline/Feline.hpp"


namespace zoo::animal::feline {
    class Cheetah final : public Feline {
    public:
        using Feline::Feline;

        std::string sound() const override { return "Chirp!"; }

        std::string description() const override { return "A fast-running spotted cat."; }

        AnimalType type() const override { return AnimalType::Cheetah; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
