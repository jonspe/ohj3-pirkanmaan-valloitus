#include "gameeventhandler.h"
#include "Game/workers/citizen.h"
#include "Game/workers/educatedcitizen.h"
#include "workers/workerbase.h"
#include "Game/buildings/city.h"
#include "core/basicresources.h"
#include "Game/core/marketplacetrader.h"
#include <QDebug>
#include <iostream>

GameEventHandler::GameEventHandler()
{
    m_tile_focuses["Animals"] = Course::BasicResource::FOOD;
    m_tile_focuses["Birch"] = Course::BasicResource::WOOD;
    m_tile_focuses["Diamond"] = Course::BasicResource::MONEY;
    m_tile_focuses["Evergreen"] = Course::BasicResource::WOOD;
    m_tile_focuses["Grass"] = Course::BasicResource::FOOD;
    m_tile_focuses["Lake"] = Course::BasicResource::FOOD;
    m_tile_focuses["Ore"] = Course::BasicResource::ORE;
    m_tile_focuses["Stone"] = Course::BasicResource::STONE;
}

bool GameEventHandler::modifyResources(std::shared_ptr<Course::PlayerBase> player, Course::ResourceMap resources)
{

    for (auto it = resources.begin(); it != resources.end(); it++){
        for (auto player_it = resources.begin(); player_it != resources.end(); player_it++){
             if (player_it->first == it->first){
                if ((m_player_resources[player].at(player_it->first) + resources.at(it->first)) >= 0){
                }else{
                 return false; // resources would go negative
                }
            }
        }
     }

    m_player_resources[player] = mergeResourceMaps(m_player_resources[player], resources);
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

    m_player_resources[player] = resource_stockpile;
}

Course::ResourceMap GameEventHandler::getResources(std::shared_ptr<Course::PlayerBase> player)
{
    return m_player_resources[player];
}

void GameEventHandler::setPlayers(std::map<std::string, std::shared_ptr<Player> > player_map)
{
    m_players = player_map;
}

void GameEventHandler::queueWorker(std::shared_ptr<Course::WorkerBase> worker_type)
{
    m_queued_worker = worker_type;
}

void GameEventHandler::addWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager)
{
    auto tile = object_manager->getTile(location);
    m_queued_worker->setResourceFocus(m_tile_focuses[tile->getType()]);
    tile->addWorker(m_queued_worker);
}

void GameEventHandler::removeWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::WorkerBase> worker_type)
{
    auto tile = object_manager->getTile(location);
    tile->removeWorker(worker_type);
}

void GameEventHandler::addBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> building_type)
{
    auto tile = object_manager->getTile(location);
    object_manager->addBuilding(building_type);
    tile->addBuilding(building_type);
    building_type->onBuildAction();
}

void GameEventHandler::removeBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> building_type)
{
    auto tile = object_manager->getTile(location);
    tile->removeBuilding(building_type);
}

void GameEventHandler::claimTile(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager)
{
    auto tile = object_manager->getTile(location);
    tile->setOwner(m_players[std::to_string(m_current_player)]);
    m_players.at(std::to_string(m_current_player))->addObject(tile);
    qDebug() << QString::fromStdString(tile->getType())
             << "claimed at "
             << tile->getCoordinatePtr()->asQpoint();
}


void GameEventHandler::firstTurn(unsigned int map_size,  std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> new_city)
{
       bool looking_for_tile = true;
       std::shared_ptr<Course::TileBase> city_tile;
       while (looking_for_tile){
           int x = -(rand() % map_size/2);
           if (m_current_player % 2){
               x = x + map_size/2 - 1;
           }
           int y = -(rand() % map_size/2);
           if (m_current_player > 2){
               y = y + map_size/2 - 1;
           }
           Course::Coordinate city_location = Course::Coordinate(x,y);
           city_tile = object_manager->getTile(city_location);
           if (city_tile->getType() == "Grass" || city_tile->getType() == "Evergreen" || city_tile->getType() == "Birch" )
           {
               claimTile(city_location, object_manager);
               addBuilding(city_location, object_manager, new_city);
               looking_for_tile = false;
           }

       }

}

void GameEventHandler::setWinner()
{
    if(not m_winner_decided)
    {
        m_winner = m_current_player;
        m_winning_turn = m_turn;
        m_winner_decided = true;
    }

}

std::tuple<unsigned int, unsigned int> GameEventHandler::getWinnerData()
{
    auto winner_data = std::make_tuple(m_winning_turn, m_winner);
    return winner_data;
}


std::tuple<unsigned int, unsigned int> GameEventHandler::passTurn(unsigned int player_amount)
{
    m_current_player++;
    if (m_current_player == player_amount + 1)
    {
        m_turn++;
        m_current_player = 1;
    }
   auto turn_data = std::make_tuple(m_turn, m_current_player);
   return turn_data;

}

MarketplaceTrader GameEventHandler::getTrader()
{
    return m_trader;
}


void GameEventHandler::resourceBought(std::shared_ptr<Player> player, Course::BasicResource resource)
{
    if(modifyResource(player, Course::BasicResource::MONEY, m_trader.getBuyPrice(resource))){
         modifyResource(player, resource, 100);
         m_trader.changeMultiplier(resource, "+");
    }

}

void GameEventHandler::resourceSold(std::shared_ptr<Player> player, Course::BasicResource resource)
{
    if(modifyResource(player, resource, -100))
    {
        modifyResource(player, Course::BasicResource::MONEY, m_trader.getSellPrice(resource));
        m_trader.changeMultiplier(resource, "-");
    }
}

