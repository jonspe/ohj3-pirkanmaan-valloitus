#ifndef BIRCH_H
#define BIRCH_H

#include "Game/tiles/elevatedtilebase.h"
#include "Game/core/resources.h"

/**
 * @brief The Birch class represents Birch in the gameworld.
 *
 * Birch has BasicProduction: \n
 * * Money = 1
 * * Food = 3
 * * Wood = 5
 * * Stone = 1
 * * Ore = 0
 *
 *
 * Tile supports 2 buildings.
 */
class Birch : public ElevatedTileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Birch() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Birch(const Course::Coordinate& location,
           const int& height,
           const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
           const std::shared_ptr<Course::iObjectManager>& objectmanager,
           const unsigned int& max_build = 1,
           const unsigned int& max_work = 13,
           const Course::ResourceMap& production = ConstResources::BIRCH_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Birch() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in Birch adds
     * one hold-marker to the building.
     *
     * Phases: \n
     * 1. Check that there is space for the building. \n
     * 2. Call parent's addBuilding \n
     * 3. Add a HoldMarker for the building. \n
     *
     * @post Exception guarantee: Strong
     * @exception OwnerConflict - If the tile's ownership prevents placing the
     * \b building.
     * @exception NoSpace - If the tile doesn't have enough space for
     * the \b building.
     */

}; // class Birch



#endif // BIRCH_H
