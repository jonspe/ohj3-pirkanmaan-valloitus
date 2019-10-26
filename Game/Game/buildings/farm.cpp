#include "farm.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

namespace Course {

Farm::Farm(
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

std::string Farm::getType() const
{
    return "Farm";
}

void Farm::onBuildAction()
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

bool Farm::canBePlacedOnTile(const std::shared_ptr<TileBase> &target) const
{
    return PlaceableGameObject::canBePlacedOnTile(target) and
            target->hasSpaceForBuildings(spacesInTileCapacity()) and(
            target->getType() == "Grass" or
            target->getType() == "Animals");
}

} // namespace Course
