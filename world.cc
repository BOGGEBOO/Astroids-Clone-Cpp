#include "world.h"

void World::update(sf::Time delta){
    for (size_t i{0}; i < objects.size(); i++){
        if (!objects[i]->update(delta, *this)){
            objects.erase(objects.begin() + 1);
            i--;
        }
    }
}

void World::render(sf::RenderWindow &to){
    for (auto &o : objects){
        o->render(to);
    }
}

void World::add(shared_ptr<Game_Object> object){
    objects.push_back(object);
}

static bool collides(Game_Object &a, Game_Object &b){
    auto distance = a.center - b.center;
    auto lengthSq = pow(distance.x, 2) + pow(distance.y, 2);
    return lengthSq <= pow(a.radius + b.radius, 2);
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