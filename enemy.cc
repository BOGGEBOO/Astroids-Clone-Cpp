#include "enemy.h"
#include "world.h"
#include "projectile.h"
#include "player.h"
#include <experimental/random>
#include <cmath>

Enemy::Enemy(const std::string &texture, const float s)
: Game_Object(texture), speed{s}, 
  random{std::experimental::randint(1, 100) * 3.600}
{}

Asteroid::Asteroid(const sf::Vector2f &pos, const float speed,
                   const std::string &texture)
: Enemy(texture, speed), type{texture}
{
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

            world.add_score(10);
            
            world.add_maxEnemies(-1);
            if (type == "images/asteroid.png") {
                sf::Vector2f projpos{shape.getPosition().x, shape.getPosition().y};
                world.add(std::make_shared<Asteroid>(projpos, 3.0f, 
                                                     "images/mini.png"));
                world.add(std::make_shared<Asteroid>(projpos, 3.0f, 
                                                     "images/mini.png"));
                world.add_maxEnemies(2);
            }
            
            return false;
        }
    }
    return true;
}

Missile::Missile(const sf::Vector2f &pos, const float speed,
                 const std::string &texture)
: Enemy(texture, speed)
{
    shape.setRotation(random);
    shape.setPosition(pos);
}

bool Missile::update(sf::Time delta, World &world)
{
    dir = world.player_pos() - shape.getPosition();

    out_of_bounds();
    shape.move(dir * delta.asSeconds() * speed);

    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {

            world.add_maxEnemies(1);
            world.add_score(10);
            return false;
        }
    }

    return true;
}

Ufo::Ufo(const sf::Vector2f &pos, const float speed,
                   const std::string &texture)
: Enemy(texture, speed)
{
    cooldown = sf::milliseconds(2000);
    //shape.setRotation(random);
    shape.setPosition(pos);
}

bool Ufo::update(sf::Time delta, World &world)
{
    dir.x = 100;

    out_of_bounds();
    shape.move(dir * delta.asSeconds() * speed);

    cooldown -= delta;
    if (cooldown <= sf::Time{}) {
        
        sf::Vector2f projpos{shape.getPosition().x, shape.getPosition().y};
        world.add(std::make_shared<Bullet>(projpos, speed,
         "images/laser.png", world.player_pos()));
        cooldown = sf::milliseconds(2000);

    }
    
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {
            world.add_maxEnemies(-1);
            world.add_score(10);
            world.add_ufo_num(-1);
            return false;
        }
    }

    return true;
}

Bullet::Bullet(const sf::Vector2f &pos, const float speed,
                   const std::string &texture, const sf::Vector2f &player)
: Enemy(texture, speed)
{
    
    shape.setPosition(pos);
    shape.setRotation(random);
    
    dir = player - shape.getPosition();
}

bool Bullet::update(sf::Time delta, World &world)
{
    shape.move(dir * delta.asSeconds() * speed);

    if (shape.getPosition().x < 0) {
        return false;
    }
    
    if (shape.getPosition().x > width) {
        return false;
    }

    if (shape.getPosition().y < 0){
        return false;
    }
    
    if (shape.getPosition().y > width) {
        return false;
    }

    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Projectile *>(collision.get())) {

            world.add_score(10);
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