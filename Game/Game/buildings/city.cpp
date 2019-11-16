#include "city.h"
#include "tiles/tilebase.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "Game/workers/educatedcitizen.h"
#include "Game/core/gameeventhandler.h"
#include <memory>

City::City(
        const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
        const std::shared_ptr<Course::iObjectManager>& objectmanager,
        const std::shared_ptr<Course::PlayerBase>& owner,
        const int& tilespaces,
        const Course::ResourceMap& buildcost,
        const Course::ResourceMap& production):
    BuildingBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        buildcost,
        production)
{
}

std::string City::getType() const
{
    return "City";
}

void City::onBuildAction()
{
    std::vector< std::shared_ptr<Course::TileBase> > neighbours;

    lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(3));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            auto event_handler = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
            auto object_manager = std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());
            auto owner = std::dynamic_pointer_cast<Player>(getOwner());

            event_handler->claimTile(getCoordinate(), object_manager, owner);
        }
    }
}

void City::doSpecialAction()
{
    std::shared_ptr<Citizen> citizen(new Citizen(lockEventHandler(),lockObjectManager(), getOwner()));
    auto event_handler = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    auto object_manager = std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());
    event_handler->addWorker(getCoordinate(),object_manager,citizen);

   object_manager->addWorker(citizen);
}



