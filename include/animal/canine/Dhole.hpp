#pragma once

#include "animal/AnimalType.hpp"
#include "animal/canine/Canine.hpp"


namespace zoo::animal::canine {
    class Dhole final : public Canine {
    public:
        using Canine::Canine;

        std::string sound() const override { return "Whistle!"; }

        std::string description() const override { return "A social wild dog from Asia."; }

        AnimalType type() const override { return AnimalType::Dhole; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
