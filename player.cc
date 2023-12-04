#include "player.h"
#include "world.h"

Player::Player(sf::Vector2f pos)
: Texture_Obj(pos, "images/player.png"), speed(1.0f)
{
    shape.setPosition(height / 2, width / 2);
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
    sf::Clock clock;
    float rotation = find_rotation();

    //auto delta = clock.restart();
    
    float spin = rotation * 250.0f * delta.asSeconds();
    center.x = 250.0*-sin(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    center.y = 250.0*cos(shape.getRotation()*3.14159265/180)*delta.asSeconds() * speed;
    
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

    std::cout << shape.getPosition().x << std::endl;
    shape.move(center);
    shape.rotate(spin);
    
    for (auto &collision : world.collides_with(*this))
    {
        return false;
    }
 
    return true;
}

void Player::render(sf::RenderWindow &to)
{
    Texture_Obj::render(to);
}