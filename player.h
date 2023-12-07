#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public Texture_Obj
{
    private:
        float speed;
        sf::Time rate;
        sf::Vector2f dir;
        float rotation;
        float spin;

    public:
        Player(const sf::Vector2f &pos);

        bool update(sf::Time delta, World &world) override;
};

#endif