#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public Texture_Obj
{
    private:
        float speed;

    public:
        Player(sf::Vector2f pos);

        bool update(sf::Time delta, World &world) override;
        void render(sf::RenderWindow &to) override;
};


#endif