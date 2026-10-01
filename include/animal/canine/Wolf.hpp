#pragma once

#include "animal/AnimalType.hpp"
#include "animal/canine/Canine.hpp"


namespace zoo::animal::canine {
    class Wolf final : public Canine {
    public:
        using Canine::Canine;

        std::string sound() const override { return "Howl!"; }

        std::string description() const override { return "A social wild canine."; }

        AnimalType type() const override { return AnimalType::Wolf; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
