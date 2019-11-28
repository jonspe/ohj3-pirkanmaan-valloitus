#include "educatedcitizen.h"
#include "Game/core/gameeventhandler.h"


EducatedCitizen::EducatedCitizen(const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                         const std::shared_ptr<Course::iObjectManager>& objectmanager,
                         const std::shared_ptr<Course::PlayerBase>& owner,
                         const int& tilespaces,
                         const Course::ResourceMap& cost,
                         const Course::ResourceMapDouble& efficiency):
    WorkerBase(
        eventhandler,
        objectmanager,
        owner,
        tilespaces,
        cost,
        efficiency)
{
}

std::string EducatedCitizen::getType() const
{
    return "Educated Citizen";
}

bool EducatedCitizen::canBePlacedOnTile(const std::shared_ptr<Course::TileBase> &target) const
{
    return target->getOwner() == getOwner() and
            WorkerBase::canBePlacedOnTile(target);
}

void EducatedCitizen::doSpecialAction()
{

}

const Course::ResourceMapDouble EducatedCitizen::tileWorkAction()
{
    auto player = getOwner();
    auto events = std::dynamic_pointer_cast<GameEventHandler>(lockEventHandler());
    double satisfaction = 0;
    Course::BasicResource focus = getResourceFocus();

   Course:: ResourceMapDouble final_modifier;

    if ( events->modifyResource(player, Course::BasicResource::FOOD, -1) )
    {
        satisfaction = 0.5;
        if ( events->modifyResource(player, Course::BasicResource::MONEY, -3) )
        {
            satisfaction = 1;
        }
    }


    if( focus != Course::BasicResource::NONE )
    {
        final_modifier[focus] =
                WORKER_EFFICIENCY.at(focus) * (satisfaction + 0.60);
    }
    else
    {
        for( auto it = WORKER_EFFICIENCY.begin();
             it != WORKER_EFFICIENCY.end();
             ++it )
        {
            final_modifier[it->first] = it->second * satisfaction;
        }
    }

    return final_modifier;
}
