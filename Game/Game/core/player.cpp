#include "player.h"



Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects) : Course::PlayerBase(name,objects)
{

}

Course::ResourceMap Player::getResources()
{
    return resource_stockpile;
}

void Player::modifyResources(Course::ResourceMap modified_resources)
{
    resource_stockpile.at(Course::BasicResource::MONEY) = modified_resources.at(Course::BasicResource::MONEY);
    resource_stockpile.at(Course::BasicResource::FOOD) = modified_resources.at(Course::BasicResource::FOOD);
    resource_stockpile.at(Course::BasicResource::WOOD) = modified_resources.at(Course::BasicResource::WOOD);
    resource_stockpile.at(Course::BasicResource::STONE) = modified_resources.at(Course::BasicResource::STONE);
    resource_stockpile.at(Course::BasicResource::ORE) = modified_resources.at(Course::BasicResource::ORE);
}

int Player::getHappiness()
{
    return happiness;
}

void Player::modifyHappiness(int happiness_change)
{
    happiness += happiness_change;
}
