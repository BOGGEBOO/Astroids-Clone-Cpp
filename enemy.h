#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy : public Texture_Obj
{
    protected:
        float speed;

    public:
        Enemy(sf::Vector2f pos, const std::string &texture);


};

class Asteroid : public Enemy
{
    public:
        Asteroid(sf::Vector2f pos);

        bool update(sf::Time delta, World &World) override;

    
    private:
        sf::Vector2f dir;
};

class Mini : public Enemy
{
    public:
        Mini(sf::Vector2f pos);
        bool update(sf::Time delta, World &World) override;
    private:
        sf::Vector2f dir;
};

class Comet : public Enemy 
{
    public:
        Comet(sf::Vector2f pos);

        bool update(sf::Time delta, World &World) override;

    
    private:
        sf::Vector2f dir;
};

#endif