#include "world.h"
#include "player.h"

void World::update(sf::Time delta){
    for (size_t i{0}; i < objects.size(); i++){
        if (!objects[i]->update(delta, *this)){
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void World::render(sf::RenderWindow &to){
    for (auto &o : objects){
        o->render(to);
    }
    sf::Text text;
    sf::Font font;
    font.loadFromFile("fonts/ARCADE_N.TTF");
    text.setFont(font);
    text.setString(std::to_string(score));
    text.setCharacterSize(20);
    text.setPosition(50.f, 50.f);
    to.draw(text);
}

void World::add(shared_ptr<Game_Object> object){
    objects.push_back(object);
}

bool World::is_dead(){
    if (!std::dynamic_pointer_cast<Player>(objects[0])){
        return true;
    }
    else{
        return false;
    }
}

static bool collides(Game_Object &a, Game_Object &b){
    // auto distance = a.center - b.center;
    // auto lengthSq = pow(distance.x, 2) + pow(distance.y, 2);
    // return lengthSq <= pow(a.radius + b.radius, 2);

    bool coll = b.shape.getGlobalBounds().intersects(a.shape.getGlobalBounds());
    return coll;
}

std::vector<shared_ptr<Game_Object>> World::collides_with(Game_Object &me) const{
    std::vector<shared_ptr<Game_Object>> result;
    
    for (auto &o : objects){
        if (o.get() == &me)
            continue;
        if (collides(*o, me))
            result.push_back(o);
    }
    return result;
}