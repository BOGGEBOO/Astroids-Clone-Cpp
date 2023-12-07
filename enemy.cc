#include "enemy.h"
#include "world.h"
#include "projectile.h"
#include <experimental/random>

Enemy::Enemy(const std::string &texture)
: Texture_Obj(texture)
{}

/// @brief Enemy type 1: Astreoid 
/// @param pos 
Asteroid::Asteroid(sf::Vector2f pos)
: Enemy("images/asteroid.png")
{
    speed = 1.0f;
    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);

    shape.setPosition(pos);
}

bool Asteroid::update(sf::Time delta, World &world)
{

    dir.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    dir.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
    out_of_bounds();

    shape.move(dir);
    
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {
            world.score += 10;
            //Ta bort när delad i två 
            world.maxEnemies--;
            sf::Vector2f projpos{shape.getPosition().x, shape.getPosition().y};
            world.add(std::make_shared<Mini>(projpos));
            world.add(std::make_shared<Mini>(projpos));
            return false;
        }
    }
    return true;
}

/// @brief Enemy type 1: Asteroid splits into two smaller asteroids (Mini) when hit
/// @param pos 
Mini::Mini(sf::Vector2f pos)
: Enemy("images/mini.png")
{
    speed = 1.0f;

    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);
    shape.setPosition(pos);
}

bool Mini::update(sf::Time delta, World &world)
{

    dir.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    dir.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;

    out_of_bounds();

    shape.move(dir);
    
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {
            world.score += 10;
            //Ta bort när dela i två fungerar
            world.maxEnemies--;
            return false;
        }
    }
    return true;
}

/// @brief Enemy type 2: Comet
/// @param pos 
Comet::Comet(sf::Vector2f pos)
: Enemy("images/comet.png")
{
    speed = 3.0f;

    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);

    shape.setPosition(pos);
};

bool Comet::update(sf::Time delta, World &world)
{

    dir.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    dir.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
    out_of_bounds();

    shape.move(dir);
    
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {
            world.score += 10;
            world.maxEnemies--;
            return false;
        }
    }
    return true;
}


void Enemy::out_of_bounds(){
    if (shape.getPosition().x < 0) {
        shape.setPosition(width, shape.getPosition().y);
    }
    
    if (shape.getPosition().x > width) {
        shape.setPosition(0, shape.getPosition().y);
    }

    if (shape.getPosition().y < 0) {
        shape.setPosition(shape.getPosition().x, height);
    }
    
    if (shape.getPosition().y > width) {
        shape.setPosition(shape.getPosition().x, 0);
    }
}