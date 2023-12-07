#include "game_object.h"
#include "texture_manager.h"
#include <algorithm>

Texture_Obj::Texture_Obj(const std::string &texture)
{
    sf::Texture *t = Texture_Manager::get(texture);
    auto size = t->getSize();
    shape.setSize(sf::Vector2f(size.x, size.y));
    shape.setTexture(t);
    shape.setOrigin(size.x / 2, size.y / 2);
}

void Texture_Obj::render(sf::RenderWindow &window)
{
    window.draw(shape);
}
