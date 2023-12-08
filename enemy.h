#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"

class Enemy : public Game_Object
{
    protected:
        const float speed;
        const double random;

        void out_of_bounds();
    public:
        Enemy(const std::string &texture, const float s);
};

class Asteroid : public Enemy
{
    public:
        Asteroid(const sf::Vector2f &pos, const float speed,
                 const std::string &texture);
        bool update(sf::Time delta, World &World) override;
    private:
        const std::string type;
};

class Missile : public Enemy
{
    public:
        Missile(const sf::Vector2f &pos, const float speed,
                const std::string &texture);
        
        bool update(sf::Time delta, World &World) override; 
};


class Ufo : public Enemy
{
    public:
        Ufo(const sf::Vector2f &pos, const float speed,
            const std::string &texture);
        
        bool update(sf::Time delta, World &World) override;

    private:
        sf::Time cooldown;
};

class Bullet : public Enemy
{
    public:
        Bullet(const sf::Vector2f &pos, const float speed,
            const std::string &texture, const sf::Vector2f &player);

        bool update(sf::Time delta, World &World) override;

};

#endif