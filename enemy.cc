#include "enemy.h"
#include "world.h"
#include "projectile.h"
#include <experimental/random>

Enemy::Enemy(sf::Vector2f pos, const std::string &texture)
: Texture_Obj(pos, texture), speed(1.0f)
{}


Asteroid::Asteroid(sf::Vector2f pos)
: Enemy(pos, "images/asteroid.png")
{
    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);

    // float rand_x = std::experimental::randint(1, int(width));
    // float rand_y = std::experimental::randint(1, int(height));
    shape.setPosition(pos);
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
    
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {
            world.score += 10;
            //Ta bort när dela i två fungerar
            world.maxEnemies--;
            sf::Vector2f projpos{shape.getPosition().x, shape.getPosition().y};
            world.add(std::make_shared<Mini>(projpos));
            world.add(std::make_shared<Mini>(projpos));
            return false;
        }
    }
    return true;
}

Mini::Mini(sf::Vector2f pos)
: Enemy(pos, "images/mini.png")
{
    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);
    shape.setPosition(pos);
}

bool Mini::update(sf::Time delta, World &world){
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

Comet::Comet(sf::Vector2f pos)
: Enemy(pos, "images/comet.png")
{
    float random = std::experimental::randint(1, 100) * 3.600;
    shape.setRotation(random);

    float rand_x = std::experimental::randint(1, int(width));
    float rand_y = std::experimental::randint(1, int(height));
    shape.setPosition(rand_x, rand_y);
};

bool Comet::update(sf::Time delta, World &world)
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
