#include "elevatedtilebase.h"


ElevatedTileBase::ElevatedTileBase(
        const Course::Coordinate &location,
        const int& height,
        const std::shared_ptr<Course::iGameEventHandler> &eventhandler,
        const std::shared_ptr<Course::iObjectManager> &objectmanager,
        const unsigned int &max_build,
        const unsigned int &max_work,
        const Course::ResourceMap &production):
    Course::TileBase(location, eventhandler, objectmanager, max_build, max_work, production)
{
    setHeight(height);
}

int ElevatedTileBase::getHeight() const
{
    return m_height;
}

void ElevatedTileBase::setHeight(int height)
{
    m_height = height;
}

