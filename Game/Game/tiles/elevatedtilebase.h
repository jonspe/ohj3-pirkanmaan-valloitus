#ifndef ELEVATEDTILEBASE_H
#define ELEVATEDTILEBASE_H

#include "tiles/tilebase.h"


class ElevatedTileBase : public Course::TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    ElevatedTileBase() = delete;

    /**
     * @brief Constructor for the class.
     *
     */
    ElevatedTileBase(const Course::Coordinate& location,
             const int& height,
             const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
             const std::shared_ptr<Course::iObjectManager>& objectmanager,
             const unsigned int& max_build = 2,
             const unsigned int& max_work = 3,
             const Course::ResourceMap& production = {}
             );

    /**
     * @brief get the height of the tile
     * @return height
     */
    int getHeight() const;

    /**
     * @brief set the height of the tile
     * @param height
     */
    void setHeight(int height);

private:
    int m_height;
};

#endif // ELEVATEDTILEBASE_H
