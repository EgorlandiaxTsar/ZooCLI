#pragma once

#include "animal/AnimalType.hpp"
#include "animal/marsupial/Marsupial.hpp"


namespace zoo::animal::marsupial {
    class Koala final : public Marsupial {
    public:
        using Marsupial::Marsupial;

        std::string sound() const override { return "Grunt!"; }

        std::string description() const override { return "A tree-dwelling eucalyptus eater."; }

        AnimalType type() const override { return AnimalType::Koala; }

        AnimalFoodType food_type() const override { return AnimalFoodType::Plants; }
    };
}
