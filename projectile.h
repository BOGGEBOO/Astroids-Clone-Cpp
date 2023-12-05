#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "game_object.h"

class Projectile : public Texture_Obj
{
    private:
        float speed;
        float rot;
        sf::Time lifetime;

    public:
        Projectile(sf::Vector2f pos, float rot);
    
        bool update(sf::Time delta, World &world) override;
};

#endif