#include "player.h"



Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects) : Course::PlayerBase(name,objects)
{

}

Course::ResourceMap Player::getResources()
{
    return resource_stockpile;
}

void Player::modifyResources(Course::ResourceMap modified_resources, std::string sign)
{
    if (sign == "+"){
        for (auto it = modified_resources.begin(); it != modified_resources.end(); it++){
            resource_stockpile.at(it->first) += modified_resources.at(it->first);
        }
    }

    else if(sign == "-"){
        for (auto it = modified_resources.begin(); it != modified_resources.end(); it++){
            resource_stockpile.at(it->first) -= modified_resources.at(it->first);
        }
    }
}

int Player::getHappiness()
{
    return happiness;
}

void Player::modifyHappiness(int happiness_change)
{
    happiness += happiness_change;
}
