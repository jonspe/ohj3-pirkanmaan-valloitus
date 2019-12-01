#include "animals.h"


Animals::Animals(const Course::Coordinate& location,
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
    setDescription("Name", "Animals");
    setDescription("Description", "Several herd animals have gathered on this field. They can be hunted for their meat, leather and furs");
}

std::string Animals::getType() const
{
    return "Animals";
}

