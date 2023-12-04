#ifndef Texture_Manager_H
#define Texture_Manager_H

#include "includes.h"
#include <map>

class Texture_Manager
{
    public:
        static sf::Texture *get(const std::string &name);

    private:
        Texture_Manager() = default;

        static Texture_Manager instance;

        std::map<std::string, std::unique_ptr<sf::Texture>> textures;
};


#endif