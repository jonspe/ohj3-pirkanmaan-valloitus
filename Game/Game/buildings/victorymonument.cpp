#include "victorymonument.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "Game/core/gameeventhandler.h"

VictoryMonument::VictoryMonument(
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
            addDescription("Victory Monument", "A majestic tribute to the ancient gods, a symbol of your rule over this land.");
}

std::string VictoryMonument::getType() const
{
    return "Victory Monument";
}


bool VictoryMonument::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
                target->getType() == "Stone" or
                target->getType() == "Grass" or
                target->getType() == "Sand");
}

void VictoryMonument::onBuildAction()
{
    auto event_handler = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    event_handler->setWinner();
}

