#include "factory.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

Factory::Factory(
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
    setDescription("Name", "Factory");
    setDescription("Description", "Creates exportable products out of wood to be sold for profit.");
}

std::string Factory::getType() const
{
    return "Factory";
}


bool Factory::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Stone" or
            target->getType() == "Grass" or
            target->getType() == "Sand");
}
