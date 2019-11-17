#include "player.h"



Player::Player(const std::string &name, const std::vector<std::shared_ptr<Course::GameObject> > objects) : Course::PlayerBase(name,objects)
{

}

void Player::generateResources(std::shared_ptr<ObjectManager> object_manager)
{
    std::vector<std::shared_ptr<Course::GameObject>> owned_tiles = getObjects();
    for(std::shared_ptr<Course::GameObject> tile : owned_tiles){
        Course::Coordinate tile_coord = tile->getCoordinate();
        std::shared_ptr<Course::TileBase> owned_tile = object_manager->getTile(tile_coord);
        owned_tile->generateResources();
    }
}

void Player::claimTile(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager)
{
    auto tile = object_manager->getTile(location);
    std::shared_ptr<Player> player = std::make_shared<Player>(this);
    tile->setOwner(player);
    addObject(tile);
}
