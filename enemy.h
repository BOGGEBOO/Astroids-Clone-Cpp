#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy : public Texture_Obj{
    public:
        Enemy(sf::Vector2f pos, const std::string &texture);
};

class Asteroid : public Enemy{
    public:
        Asteroid(sf::Vector2f pos);

        bool update(sf::Time delta, World &World) override;
};

#endif