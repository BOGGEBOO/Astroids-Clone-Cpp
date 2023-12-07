#include "world.h"
#include "player.h"

World::World()
{
    font.loadFromFile("fonts/ARCADE_N.TTF");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(50.f, 50.f);
}

void World::update(sf::Time delta) {
    for (size_t i{0}; i < objects.size(); i++) {
        if (!objects[i]->update(delta, *this)) {
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

void World::render(sf::RenderWindow &to) {
    for (auto &o : objects){
        o->render(to);
    }

    //draw score
    text.setString("Score: " + std::to_string(score));
    to.draw(text);
}

void World::add(shared_ptr<Game_Object> object){
    objects.push_back(object);
}

//check if player is dead
bool World::is_dead() const {
    if (!std::dynamic_pointer_cast<Player>(objects[0])) {
        return true;
    }
    else{
        return false;
    }
}

static bool collides(Game_Object &a, Game_Object &b) {

    bool coll = b.shape.getGlobalBounds().intersects(a.shape.getGlobalBounds());
    return coll;

}

std::vector<shared_ptr<Game_Object>> World::collides_with(Game_Object &me) const {
    
    std::vector<shared_ptr<Game_Object>> result;
    
    for (auto &o : objects) {

        if (o.get() == &me)
            continue;
        if (collides(*o, me))
            result.push_back(o);

    }
    return result;
}