#include "advancedlumbercamp.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

AdvancedLumberCamp::AdvancedLumberCamp(
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
    setDescription("Name", "Advanced Lumber Camp");
    setDescription("Description", "With new tools created of rare minerals, wood production is faster than ever.");
}

std::string AdvancedLumberCamp::getType() const
{
    return "Advanced Lumber Camp";
}


bool AdvancedLumberCamp::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Birch" or
            target->getType() == "Evergreen");

}
