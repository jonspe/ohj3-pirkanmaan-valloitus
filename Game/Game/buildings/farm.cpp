#include "farm.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

Farm::Farm(
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
                addDescription("Farm", "A sustainable source of food is essential for the survival of any civilization.");
}

std::string Farm::getType() const
{
    return "Farm";
}


bool Farm::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Grass" or
            target->getType() == "Animals");
}
