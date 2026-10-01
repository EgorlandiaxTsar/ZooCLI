#pragma once

#include "animal/Animal.hpp"
#include "animal/AnimalFoodType.hpp"


namespace zoo::animal::marsupial {
    class Marsupial : public Animal {
    public:
        using Animal::Animal;

        AnimalFoodType food_type() const override { return AnimalFoodType::Plants; }
    };
}
