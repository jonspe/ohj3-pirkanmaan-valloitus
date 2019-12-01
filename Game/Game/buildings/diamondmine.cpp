#include "diamondmine.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

DiamondMine::DiamondMine(
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
    setDescription("Name", "Diamond Mine");
    setDescription("Description", "So we back in the mine, got our pickaxe swinging from side to side...");
}

std::string DiamondMine::getType() const
{
    return "Diamond Mine";
}


bool DiamondMine::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Diamond");
}

