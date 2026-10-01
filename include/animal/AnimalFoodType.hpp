#pragma once


namespace zoo::animal {
    enum class AnimalFoodType {
        Meat,
        Plants,
        Insects,
        Omnivore
    };

    inline std::string animal_food_type_to_string(const AnimalFoodType food_type) {
        switch (food_type) {
            case AnimalFoodType::Meat: return "Meat";
            case AnimalFoodType::Plants: return "Plants";
            case AnimalFoodType::Insects: return "Insects";
            case AnimalFoodType::Omnivore: return "Omnivore";
        }
        throw exception::ZooException("Failed to convert AnimalFoodType to string");
    }

    inline AnimalFoodType animal_food_type_from_string(const std::string_view str) {
        if (str == "Meat") return AnimalFoodType::Meat;
        if (str == "Plants") return AnimalFoodType::Plants;
        if (str == "Insects") return AnimalFoodType::Insects;
        if (str == "Omnivore") return AnimalFoodType::Omnivore;

        throw exception::ZooException("Failed to convert string to AnimalFoodType");
    }
}
