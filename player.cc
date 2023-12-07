#include "player.h"
#include "world.h"
#include "enemy.h"
#include "projectile.h"

Player::Player(const sf::Vector2f &pos)
: Texture_Obj("images/player.png"), speed(1.0f), rate{sf::milliseconds(1000)}
{
    shape.setPosition(pos);
}

float find_rotation(){
    float rotation{0};
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        rotation -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        rotation += 1;
    
    return rotation;
}

bool Player::update(sf::Time delta, World &world)
{
    rotation = find_rotation();

    spin = rotation * 250.0f * delta.asSeconds();
    dir.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    dir.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        speed += 0.05f * delta.asMicroseconds() / 10000.0f;
    }
    else if (speed > 0){
        speed -=0.02f * delta.asMicroseconds() / 10000.0f;
    }
    //Maximum velocity
    if (speed > 5.0f){
        speed = 5.0f;
    }

    //respawn player on the opposite side
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

    //shoot projectile from player position
    rate -= delta;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && rate <= sf::Time{}) {
        
        sf::Vector2f projpos{shape.getPosition().x, shape.getPosition().y};
        world.add(std::make_shared<Projectile>(projpos, shape.getRotation()));
        rate = sf::milliseconds(300);

    }

    shape.move(dir);
    shape.rotate(spin); 

    //check collision
    for (auto &collision : world.collides_with(*this))
    {
        if (dynamic_cast<Enemy *>(collision.get())) {
            return false;
        }
    }
 
    return true;
}