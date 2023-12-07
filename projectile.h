#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"

class Projectile : public Game_Object
{
    private:
        const float speed;
        const float rot;
        sf::Vector2f dir;

    public:
        Projectile(const sf::Vector2f &pos, const float r);
    
        bool update(sf::Time delta, World &world) override;
};

#endif