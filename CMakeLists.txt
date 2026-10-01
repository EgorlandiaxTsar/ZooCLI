cmake_minimum_required(VERSION 4.3)
project(ZooCLI)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        replxx
        GIT_REPOSITORY https://github.com/AmokHuginnsson/replxx.git
        GIT_TAG master
)

FetchContent_Declare(
        json
        URL https://github.com/nlohmann/json/releases/download/v3.12.0/json.tar.xz
)

FetchContent_MakeAvailable(replxx json)

add_executable(ZooCLI main.cpp)

target_sources(ZooCLI PRIVATE
        src/cli/Cli.cpp
        src/cli/CommandParser.cpp
        src/env/Environment.cpp
        src/persistence/JsonStore.cpp
        src/zoo/Zoo.cpp
)

target_include_directories(ZooCLI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(ZooCLI
        PRIVATE
        replxx
        nlohmann_json::nlohmann_json
)