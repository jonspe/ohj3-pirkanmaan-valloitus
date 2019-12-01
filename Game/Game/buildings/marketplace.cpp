#include "marketplace.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

Marketplace::Marketplace(
        const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
        const std::shared_ptr<Course::iObjectManager>& objectmanager,
        const std::shared_ptr<Course::PlayerBase>& owner,
        const int& tilespaces,
        const Course::ResourceMap& buildcost,
        const Course::ResourceMap& production
        ):
    BuildingBase(eventhandler,
                 objectmanager,
                 owner,
                 tilespaces,
                 buildcost,
                 production)
{
    setDescription("Name", "Marketplace");
    setDescription("Description", "A place to exchange goods with foreign merchants.");
}

std::string Marketplace::getType() const
{
    return "Marketplace";
}


bool Marketplace::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Stone" or
            target->getType() == "Grass" or
            target->getType() == "Sand");
}

void Marketplace::doSpecialAction()
{

}

