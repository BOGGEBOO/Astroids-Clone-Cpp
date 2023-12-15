#ifndef PLAYER_H
#define PLAYER_H

#include "game_object.h"

class Player : public Game_Object
{
    private:
        float speed;
        sf::Time rate;
        float rotation;
  bool invincible{false};
        float spin;
  

    public:
        Player(const sf::Vector2f &pos);

        bool update(sf::Time delta, World &world) override;

};

#endif
