#include "advancedfarm.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

AdvancedFarm::AdvancedFarm(
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
         addDescription("Advanced Farm", "More food can be produced thanks to improved farming methods.");
}

std::string AdvancedFarm::getType() const
{
    return "Advanced Farm";
}


bool AdvancedFarm::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Grass" or
            target->getType() == "Animals");
}
