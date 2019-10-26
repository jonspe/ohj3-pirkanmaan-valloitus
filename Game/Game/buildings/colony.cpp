#include "colony.h"
#include "interfaces/iobjectmanager.h"
#include "tiles/tilebase.h"

namespace Course {

Colony::Colony(
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

std::string Colony::getType() const
{
    return "Colony";
}

void Colony::onBuildAction()
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

ResourceMap Colony::getProduction()
{
    return PRODUCTION_EFFECT;
}

} // namespace Course
