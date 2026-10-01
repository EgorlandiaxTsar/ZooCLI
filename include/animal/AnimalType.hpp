#pragma once
#include "exception/ZooException.hpp"


namespace zoo::animal {
    enum class AnimalType {
        Tiger,
        Lion,
        Cheetah,
        Jaguar,

        Crocodile,
        Alligator,
        KomodoDragon,
        Iguana,

        Kangaroo,
        Koala,
        Wombat,
        TasmanianDevil,

        Wolf,
        RedFox,
        ArcticFox,
        Dhole
    };

    inline std::string animal_type_to_string(const AnimalType type) {
        switch (type) {
            case AnimalType::Tiger: return "Tiger";
            case AnimalType::Lion: return "Lion";
            case AnimalType::Cheetah: return "Cheetah";
            case AnimalType::Jaguar: return "Jaguar";

            case AnimalType::Crocodile: return "Crocodile";
            case AnimalType::Alligator: return "Alligator";
            case AnimalType::KomodoDragon: return "Komodo Dragon";
            case AnimalType::Iguana: return "Iguana";

            case AnimalType::Kangaroo: return "Kangaroo";
            case AnimalType::Koala: return "Koala";
            case AnimalType::Wombat: return "Wombat";
            case AnimalType::TasmanianDevil: return "Tasmanian Devil";

            case AnimalType::Wolf: return "Wolf";
            case AnimalType::RedFox: return "Red Fox";
            case AnimalType::ArcticFox: return "Arctic Fox";
            case AnimalType::Dhole: return "Dhole";
        }
        throw exception::ZooException("Failed to convert AnimalType to string");
    }

    inline AnimalType animal_type_from_string(const std::string_view str) {
        if (str == "Tiger") return AnimalType::Tiger;
        if (str == "Lion") return AnimalType::Lion;
        if (str == "Cheetah") return AnimalType::Cheetah;
        if (str == "Jaguar") return AnimalType::Jaguar;

        if (str == "Crocodile") return AnimalType::Crocodile;
        if (str == "Alligator") return AnimalType::Alligator;
        if (str == "Komodo Dragon") return AnimalType::KomodoDragon;
        if (str == "Iguana") return AnimalType::Iguana;

        if (str == "Kangaroo") return AnimalType::Kangaroo;
        if (str == "Koala") return AnimalType::Koala;
        if (str == "Wombat") return AnimalType::Wombat;
        if (str == "Tasmanian Devil") return AnimalType::TasmanianDevil;

        if (str == "Wolf") return AnimalType::Wolf;
        if (str == "Red Fox") return AnimalType::RedFox;
        if (str == "Arctic Fox") return AnimalType::ArcticFox;
        if (str == "Dhole") return AnimalType::Dhole;

        throw exception::ZooException("Failed to convert string to AnimalType");
    }
}
