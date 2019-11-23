#include "lumbercamp.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

LumberCamp::LumberCamp(
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
                addDescription("Lumber Camp", "Wood is abundant and is used everywhere in construction.");
}

std::string LumberCamp::getType() const
{
    return "Lumber Camp";
}


bool LumberCamp::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Birch" or
            target->getType() == "Evergreen");

}
