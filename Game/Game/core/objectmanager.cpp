#include "objectmanager.h"
#include "tiles/tilebase.h"
#include "Game/tiles/elevatedtilebase.h"
#include <vector>
#include <memory>

ObjectManager::ObjectManager()
{

}

void ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++){
        m_tile_data.push_back(*it);
    }
}

std::shared_ptr<Course::TileBase>ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for (auto it = m_tile_data.begin(); it != m_tile_data.end(); it++){
        if (it->get()->getCoordinate() == coordinate){
            return *it;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> ObjectManager::getTile(const Course::ObjectId &id)
{
    for (auto it = m_tile_data.begin(); it != m_tile_data.end(); it++){
        if (it->get()->ID == id){
            return *it;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase>> ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    std::vector<std::shared_ptr<Course::TileBase>> wanted_tiles;

    for (auto it = m_tile_data.begin(); it != m_tile_data.end(); it++){ // iterate through tiles, then coordinates to find wanted tiles
        for (auto coord_it = coordinates.begin(); coord_it != coordinates.end(); coord_it++){
            if(it->get()->getCoordinate() == *coord_it){
                wanted_tiles.push_back(*it);
            }
        }
    }

    if (wanted_tiles.size() == 0){
        wanted_tiles.push_back(nullptr);
    }
    return wanted_tiles;
}


std::vector<std::shared_ptr<Course::TileBase> > ObjectManager::getAllTiles()
{
    return m_tile_data;
}

void ObjectManager::addBuilding(std::shared_ptr<Course::BuildingBase> building)
{
    m_buildings.push_back(building);
}

void ObjectManager::addWorker(std::shared_ptr<Course::WorkerBase> worker)
{
    m_workers.push_back(worker);
}
