#pragma once

#include "animal/AnimalType.hpp"
#include "animal/reptile/Reptile.hpp"


namespace zoo::animal::reptile {
    class KomodoDragon final : public Reptile {
    public:
        using Reptile::Reptile;

        std::string sound() const override { return "Hiss!"; }

        std::string description() const override { return "A large predatory lizard."; }

        AnimalType type() const override { return AnimalType::KomodoDragon; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
