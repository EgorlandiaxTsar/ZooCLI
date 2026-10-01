#pragma once

#include "animal/AnimalType.hpp"
#include "animal/canine/Canine.hpp"


namespace zoo::animal::canine {
    class SweetieFox final : public Canine {
    public:
        using Canine::Canine;

        std::string sound() const override { return "Yip!"; }

        std::string description() const override { return "A small adaptable wild canine."; }

        AnimalType type() const override { return AnimalType::RedFox; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Omnivore; }
    };
}
