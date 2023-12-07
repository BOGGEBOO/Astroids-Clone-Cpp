#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy : public Texture_Obj
{
    protected:
        const float speed;
        sf::Vector2f dir;
        const double random;

        void out_of_bounds();
    public:
        Enemy(const std::string &texture, const float s);
};

class Asteroid : public Enemy
{
    public:
        Asteroid(const sf::Vector2f &pos);
        bool update(sf::Time delta, World &World) override;

};

class Mini : public Enemy
{
    public:
        Mini(const sf::Vector2f &pos);
        bool update(sf::Time delta, World &World) override;
};

class Comet : public Enemy 
{
    public:
        Comet(const sf::Vector2f &pos);
        bool update(sf::Time delta, World &World) override;
};

#endif