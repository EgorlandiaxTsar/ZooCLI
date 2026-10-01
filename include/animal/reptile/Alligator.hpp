#pragma once

#include "animal/AnimalType.hpp"
#include "animal/reptile/Reptile.hpp"


namespace zoo::animal::reptile {
    class Alligator final : public Reptile {
    public:
        using Reptile::Reptile;

        std::string sound() const override { return "Hiss!"; }

        std::string description() const override { return "A large freshwater reptile."; }

        AnimalType type() const override { return AnimalType::Alligator; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
