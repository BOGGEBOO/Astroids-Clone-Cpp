#include "projectile.h"
#include "world.h"
#include "enemy.h"

Projectile::Projectile(const sf::Vector2f &pos, const float r)
: Game_Object("images/projectile1.png"), speed(5.0f), rot{r}
{
    shape.setPosition(pos);
    shape.setRotation(rot);
}

bool Projectile::update(sf::Time delta, World &world)
{
    dir.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    dir.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
    shape.move(dir);

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

    return true;   
}