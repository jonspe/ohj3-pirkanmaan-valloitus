#include "university.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"
#include "Game/workers/educatedcitizen.h"
#include "Game/core/gameeventhandler.h"
#include <memory>

University::University(
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
              addDescription("University", "A place where citizens can be educated to be more efficient in their work.");
}

std::string University::getType() const
{
    return "University";
}

void University::doSpecialAction()
{
    std::shared_ptr<EducatedCitizen> educated_citizen(new EducatedCitizen(lockEventHandler(),lockObjectManager(), getOwner()));
    auto event_handler = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    auto object_manager = std::dynamic_pointer_cast<ObjectManager>(lockObjectManager());
    event_handler->queueWorker(educated_citizen);
    object_manager->addWorker(educated_citizen);

}


bool University::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Stone" or
            target->getType() == "Grass" or
            target->getType() == "Sand");
}

