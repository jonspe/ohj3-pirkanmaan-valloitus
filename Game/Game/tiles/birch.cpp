#include "birch.h"

namespace Course {

Birch::Birch(const Coordinate& location,
                     const std::shared_ptr<iGameEventHandler>& eventhandler,
                     const std::shared_ptr<iObjectManager>& objectmanager,
                     const unsigned int& max_build,
                     const unsigned int& max_work,
                     const ResourceMap& production):
    TileBase(location,
             eventhandler,
             objectmanager,
             max_build,
             max_work,
             production)
{
}

std::string Birch::getType() const
{
    return "Birch";
}

} // namespace Course
