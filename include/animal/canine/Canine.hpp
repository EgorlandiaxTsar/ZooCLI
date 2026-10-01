#pragma once

#include "animal/Animal.hpp"
#include "animal/AnimalFoodType.hpp"


namespace zoo::animal::canine {
    class Canine : public Animal {
    public:
        using Animal::Animal;

        AnimalFoodType food_type() const override { return AnimalFoodType::Meat; }
    };
}
