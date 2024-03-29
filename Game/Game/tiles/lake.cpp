#include "lake.h"


Lake::Lake(const Course::Coordinate& location,
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
    setDescription("Name", "Lake");
    setDescription("Description",  "A large body of water with plenty of fish.");
}

std::string Lake::getType() const
{
    return "Lake";
}

