/*
** EPITECH PROJECT, 2025
** main
** File description:
** main
*/
#include <libconfig.h++>
#include <iostream>
#include <dlfcn.h>
#include "tools/Error.hpp"
#include "Builder/Builder.hpp"

int main(int ac, char **av) {
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " <config_file>" << std::endl;
        return 84;
    }
    if (static_cast<std::string>(av[1]) == "-h" || static_cast<std::string>(av[1]) == "--help") {
        std::cout << "Usage: ./raytracer <SCENE_FILE>" << std::endl;
        std::cout << "  SCENE_FILE: scene configuration" << std::endl;
        return 0;
    } 
    try {
        Builder builder(av[1]);
        builder.loadAll();
    } catch (const libconfig::FileIOException &fioex) {
        std::cerr << "I/O error while reading file." << std::endl;
        return 84;
    } catch (const libconfig::SettingNotFoundException &nfex) {
        std::cerr << "Setting not found: " << nfex.getPath() << std::endl;
        return 84;
    } catch (const libconfig::ConfigException &cex) {
        std::cerr << "Configuration error: " << cex.what() << std::endl;
        return 84;
    } catch (const tools::Error &e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 84;
    }
    return 0;
}
