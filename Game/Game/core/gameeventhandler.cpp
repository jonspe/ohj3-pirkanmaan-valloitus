#include "gameeventhandler.h"
#include "Game/workers/citizen.h"
#include "Game/workers/educatedcitizen.h"
#include "workers/workerbase.h"
GameEventHandler::GameEventHandler()
{

}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{

    for (auto it = resources.begin(); it != resources.end(); it++){
        if (player_resources[player].at(it->first) > 0){
           player_resources[player].at(it->first) += resources.at(it->first);
        }else{
           if (player_resources[player].at(it->first) - resources.at(it->first) >= 0){
                player_resources[player].at(it->first) -= resources.at(it->first);
           }else{
               return false;
           }
        }
    }
    return true;
}

bool GameEventHandler::modifyResource(std::shared_ptr<Course::PlayerBase> player, Course::BasicResource resource, int amount)
{

    Course::ResourceMap resource_in_map;
    resource_in_map[resource] = amount;
    return modifyResources(player, resource_in_map);

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

void GameEventHandler::addWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::PlayerBase> player, std::shared_ptr<Course::WorkerBase> worker_type)
{
    auto tile = object_manager->getTile(location);
    std::shared_ptr<GameEventHandler> event_handler(this);

}

void GameEventHandler::addBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::PlayerBase> player, std::shared_ptr<Course::BuildingBase> building_type)
{
    auto tile = object_manager->getTile(location);
    std::shared_ptr<GameEventHandler> event_handler(this);

}


