#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy : public Texture_Obj
{
    protected:
        float speed;
        sf::Vector2f dir;

        void out_of_bounds();
    public:
        Enemy(const std::string &texture);


};

class Asteroid : public Enemy
{
    public:
        Asteroid(sf::Vector2f pos);

        bool update(sf::Time delta, World &World) override;

};

class Mini : public Enemy
{
    public:
        Mini(sf::Vector2f pos);
        bool update(sf::Time delta, World &World) override;
};

class Comet : public Enemy 
{
    public:
        Comet(sf::Vector2f pos);

        bool update(sf::Time delta, World &World) override;
};

#endif