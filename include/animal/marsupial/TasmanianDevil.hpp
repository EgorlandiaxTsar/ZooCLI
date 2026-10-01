#pragma once

#include "animal/AnimalType.hpp"
#include "animal/marsupial/Marsupial.hpp"


namespace zoo::animal::marsupial {
    class TasmanianDevil final : public Marsupial {
    public:
        using Marsupial::Marsupial;

        std::string sound() const override { return "Growl!"; }

        std::string description() const override { return "A small but aggressive carnivorous marsupial."; }

        AnimalType type() const override { return AnimalType::TasmanianDevil; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
