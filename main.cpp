#include "cli/Cli.hpp"
#include "env/Environment.hpp"

int main() {
    zoo::env::Environment environment;
    zoo::cli::Cli cli(environment);
    cli.run();
    return 0;
}
