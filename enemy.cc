#include "enemy.h"
#include "world.h"
#include <experimental/random>

Enemy::Enemy(sf::Vector2f pos, const std::string &texture)
: Texture_Obj(pos, texture), speed(1.0f)
{}


Asteroid::Asteroid(sf::Vector2f pos)
: Enemy(pos, "images/player.png")
{
    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);
}

bool Asteroid::update(sf::Time delta, World &world)
{

    center.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    center.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    

    if (shape.getPosition().x < 0){
        shape.setPosition(width, shape.getPosition().y);
    }
    
    if (shape.getPosition().x > width) {
        shape.setPosition(0, shape.getPosition().y);
    }

    if (shape.getPosition().y < 0){
        shape.setPosition(shape.getPosition().x, height);
    }
    
    if (shape.getPosition().y > width) {
        shape.setPosition(shape.getPosition().x, 0);
    }

    shape.move(center);
    
    // for (auto &collision : world.collides_with(*this))
    // {
    //     return false;
    // }
    return true;
}
