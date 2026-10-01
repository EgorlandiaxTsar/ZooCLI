#pragma once

#include "animal/AnimalType.hpp"
#include "animal/canine/Canine.hpp"


namespace zoo::animal::canine {
    class ArcticFox final : public Canine {
    public:
        using Canine::Canine;

        std::string sound() const override { return "Yip!"; }

        std::string description() const override { return "A small fox adapted to polar climates."; }

        AnimalType type() const override { return AnimalType::ArcticFox; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Omnivore; }
    };
}
