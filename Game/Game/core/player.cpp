#include "player.h"



Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects) : Course::PlayerBase(name,objects)
{

}


int Player::getHappiness()
{
    return happiness;
}

void Player::modifyHappiness(int happiness_change)
{
    happiness += happiness_change;
}

