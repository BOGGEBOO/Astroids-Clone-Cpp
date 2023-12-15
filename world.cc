#include "world.h"
#include "player.h"

/**
 * Class that checks all objects on screen
*/
World::World()
{
    font.loadFromFile("fonts/ARCADE_N.TTF");
    text.setFont(font);
    text.setCharacterSize(20);
    text.setPosition(50.f, 50.f);
}

/**
 * Calls update for all objects and removes them if required
*/
void World::update(sf::Time delta) {
    for (size_t i{0}; i < objects.size(); i++) {
        if (!objects[i]->update(delta, *this)) {
            objects.erase(objects.begin() + i);
            i--;
        }
    }
}

/**
 * Calls render for all objects 
*/
void World::render(sf::RenderWindow &to) {
    for (auto &o : objects){
        o->render(to);
    }

    //draw score
    text.setString("Score: " + std::to_string(score));
    to.draw(text);
}

/**
 * Adds a game object
*/
void World::add(shared_ptr<Game_Object> object){
    objects.push_back(object);
}

/**
 * check if player is dead
 */
bool World::is_dead() const {
    if (!std::dynamic_pointer_cast<Player>(objects[0])) {
        return true;
    }
    else{
        return false;
    }
}

/**
 * Gets the players position
*/
sf::Vector2f World::player_pos() const {
    return objects[0]->shape.getPosition();
}

/**
 * Getter for the score variable
*/
int World::get_score(){
    return score;
}

/**
 * Adds to the score variable
*/
void World::add_score(int s){
    score += s;
}

/**
 * Getter for the maxEnemies variable
*/
int World::get_maxEnemies(){
    return maxEnemies;
}

/**
 * Adds to the maxEnemies variable
*/
void World::add_maxEnemies(int m){
    maxEnemies += m;
}

/**
 * Getter for the ufo_num variable
*/
int World::get_ufo_num(){
    return ufo_num;
}

/**
 * Adds to the ufo_num variable
*/
void World::add_ufo_num(int u){
    ufo_num += u;
}

/**
 * Returns true when two objects collide
*/
static bool collides(Game_Object &a, Game_Object &b) {

    bool coll = b.shape.getGlobalBounds().intersects(a.shape.getGlobalBounds());
    return coll;

}

/**
 * Addes collided objects to a vector and returns it
*/
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