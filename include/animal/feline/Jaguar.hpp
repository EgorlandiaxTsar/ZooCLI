#pragma once

#include "animal/AnimalType.hpp"
#include "animal/feline/Feline.hpp"


namespace zoo::animal::feline {
    class Jaguar final : public Feline {
    public:
        using Feline::Feline;

        std::string sound() const override { return "Growl!"; }

        std::string description() const override { return "A powerful spotted cat from the Americas."; }

        AnimalType type() const override { return AnimalType::Jaguar; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
