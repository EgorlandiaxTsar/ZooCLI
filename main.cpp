#include <filesystem>
#include <iostream>

#include "animal/feline/Lion.hpp"
#include "cli/Cli.hpp"
#include "env/Environment.hpp"
#include "persistence/JsonStore.hpp"

int main() {
    zoo::env::Environment environment;
    zoo::cli::Cli cli(environment);
    cli.run();
    return 0;
}
