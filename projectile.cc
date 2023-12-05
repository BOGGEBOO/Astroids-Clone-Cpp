#include "projectile.h"
#include "world.h"
#include "enemy.h"

Projectile::Projectile(sf::Vector2f pos, float rot)
: Texture_Obj(pos, "images/player.png"), speed(1.0f), rot{rot}, lifetime{sf::milliseconds(500)}
{
    shape.setPosition(pos);
    shape.setRotation(rot);
}

bool Projectile::update(sf::Time delta, World &world)
{
    center.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    center.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
    shape.move(center);


    if (shape.getPosition().x < 0){
        std::cout << "bort" << std::endl;
        return false;
    }
    
    if (shape.getPosition().x > width) {
        std::cout << "bort" << std::endl;
        return false;
    }

    if (shape.getPosition().y < 0){
        std::cout << "bort" << std::endl;
        return false;
    }
    
    if (shape.getPosition().y > width) {
        std::cout << "bort" << std::endl;
        return false;
    }

    // if(delta.asMilliseconds() > lifetime.asMilliseconds()){
    //     std::cout << "bort" << std::endl;
    //     return false;
    // }

    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Enemy *>(collision.get())) {
            std::cout << "hit" << std::endl;
        }
    }

    return true;   
}