#include "texture_manager.h"
#include <stdexcept>

sf::Texture *Texture_Manager::get(const std::string &name){
    auto found = instance.textures.find(name);
    if (found != instance.textures.end())
        return found->second.get();

    sf::Texture *t = new sf::Texture();
    if (!t->loadFromFile(name))
        throw std::logic_error("FEL: Ingen textur");

    instance.textures.insert(std::make_pair(name, std::unique_ptr<sf::Texture>(t)));
    return t;
}


Texture_Manager Texture_Manager::instance;