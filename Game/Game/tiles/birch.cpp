#include "birch.h"


Birch::Birch(const Course::Coordinate& location,
                     const int& height,
                     const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
                     const std::shared_ptr<Course::iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const Course::ResourceMap& production):
    ElevatedTileBase(
             location,
             height,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{ 
    setDescription("Name", "Birch");
    setDescription("Description", "A forest of hundreds of beautiful birch trees.");
}

std::string Birch::getType() const
{
    return "Birch";


} // namespace Course
