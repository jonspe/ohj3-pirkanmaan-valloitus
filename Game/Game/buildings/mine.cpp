#include "mine.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

namespace Course {

Mine::Mine(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const int& tilespaces,
        const ResourceMap& buildcost,
        const ResourceMap& production
        ):
    BuildingBase(eventhandler,
                 objectmanager,
                 owner,
                 tilespaces,
                 buildcost,
                 production)
{
}

std::string Mine::getType() const
{
    return "Mine";
}

void Mine::onBuildAction()
{
    std::vector< std::shared_ptr<TileBase> > neighbours;

    lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(2));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}

bool Mine::canBePlacedOnTile(const std::shared_ptr<TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Stone" or
            target->getType() == "Ore" or
            target->getType() == "Diamonds");
}

} // namespace Course
