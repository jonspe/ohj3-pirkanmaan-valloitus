#include "stone.h"

Stone::Stone(const Course::Coordinate& location,
                     const int& height,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const Course::ResourceMap& production):
    ElevatedTileBase(location,
             height,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{
    setDescription("Name", "Stone");
    setDescription("Description", "Rocky, uninhabitable terrain.");
}

std::string Stone::getType() const
{
    return "Stone";
}


