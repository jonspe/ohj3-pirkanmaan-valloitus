#include "gameeventhandler.h"

GameEventHandler::GameEventHandler()
{

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{
    for (auto it = resources.begin(); it != resources.end(); it++){
        if (player_resources[player].at(it->first) > 0){
           player_resources[player].at(it->first) += resources.at(it->first);
        }else{
           player_resources[player].at(it->first) -= resources.at(it->first);
        }
    }
    return true;
}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{

    Course::ResourceMap resource_in_map;
    resource_in_map[resource] = amount;
    modifyResources(player, resource_in_map);
    return true;
}

void GameEventHandler::setPresetResources(std::shared_ptr<Course::PlayerBase> player)
{
    Course::ResourceMap resource_stockpile = {
        {Course::BasicResource::MONEY, 200},
        {Course::BasicResource::FOOD, 200},
        {Course::BasicResource::WOOD, 200},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 0}

    };

    player_resources[player] = resource_stockpile;
}

Course::ResourceMap GameEventHandler::getResources(std::shared_ptr<Course::PlayerBase> player)
{
    return player_resources[player];
}


