#pragma once

#include <memory>
#include <string>

#include "zoo/Zoo.hpp"


namespace zoo::env {
    class Environment {
    public:
        void add_zoo(const std::string &name, int food_reserve, int cages_count);
        void remove_zoo(const std::string &name);
        zoo::Zoo &zoo(const std::string &name);
        void clear();

        const std::vector<std::unique_ptr<zoo::Zoo> > &zoos() const { return zoos_; }

    protected:
        std::vector<std::unique_ptr<zoo::Zoo> > zoos_;

        zoo::Zoo *find_zoo_by_name(const std::string &name, bool destructive = false);

        std::vector<std::unique_ptr<zoo::Zoo> >::iterator find_slot_by_name(const std::string &name, bool destructive = false);
    };
}
