#include "objectmanager.h"
#include <vector>
#include "tiles/tilebase.h"

Course::ObjectManager::ObjectManager()
{

}

void Course::ObjectManager::addTiles(const std::vector<std::shared_ptr<Course::TileBase>> &tiles)
{
    for (auto it = tiles.begin(); it != tiles.end(); it++){
        managed_tiles.push_back(*it);
    }
}

std::shared_ptr<Course::TileBase> Course::ObjectManager::getTile(const Course::Coordinate &coordinate)
{
    for (auto it = managed_tiles.begin(); it != managed_tiles.end(); it++){
        if (it->get()->getCoordinate() == coordinate){
            return *it;
        }
    }
    return nullptr;
}

std::shared_ptr<Course::TileBase> Course::ObjectManager::getTile(const Course::ObjectId &id)
{
    for (auto it = managed_tiles.begin(); it != managed_tiles.end(); it++){
        if (it->get()->ID == id){
            return *it;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Course::TileBase> > Course::ObjectManager::getTiles(const std::vector<Course::Coordinate> &coordinates)
{
    wanted_tiles.clear();

    for (auto it = managed_tiles.begin(); it != managed_tiles.end(); it++){ // iterate through tiles, then coordinates to find wanted tiles
        for (auto coord_it = coordinates.begin(); coord_it != coordinates.end(); it++){
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


