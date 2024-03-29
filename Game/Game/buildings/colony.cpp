#include "colony.h"
#include "interfaces/iobjectmanager.h"
#include "Game/core/gameeventhandler.h"
#include "tiles/tilebase.h"

Colony::Colony(
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
    setDescription("Name", "Colony");
    setDescription("Description", "Colonizing new areas allows you access to new resources. You will also have more mouths to feed, however.");
}

std::string Colony::getType() const
{
    return "Colony";
}

void Colony::onBuildAction()
{
    std::vector< std::shared_ptr<Course::TileBase> > neighbours = lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(2));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            auto event_handler = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
            auto object_manager = std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());

            event_handler->claimTile(*it->get()->getCoordinatePtr(), object_manager);
        }
    }
}

