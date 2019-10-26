#include "city.h"
#include "tiles/tilebase.h"


namespace Course {

City::City(
        const std::shared_ptr<iGameEventHandler>& eventhandler,
        const std::shared_ptr<iObjectManager>& objectmanager,
        const std::shared_ptr<PlayerBase>& owner,
        const int& tilespaces,
        const ResourceMap& buildcost,
        const ResourceMap& production):
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
    std::vector< std::shared_ptr<TileBase> > neighbours;

    lockObjectManager()->getTiles(getCoordinatePtr()->neighbours(3));

    for(auto it = neighbours.begin(); it != neighbours.end(); ++it)
    {
        // If the Tile doesn't have owner, set it's owner to buildings owner.
        if( not (*it)->getOwner() )
        {
            (*it)->setOwner(getOwner());
        }
    }
}


} // namespace Course
