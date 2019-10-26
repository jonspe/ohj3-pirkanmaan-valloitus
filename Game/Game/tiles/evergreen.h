#ifndef Evergreen_H
#define Evergreen_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"

namespace Course {

/**
 * @brief The Evergreen class represents Evergreen in the gameworld.
 *
 * Evergreen has BasicProduction: \n
 * * Money = 1
 * * Food = 2
 * * Wood = 6
 * * Stone = 1
 * * Ore = 0
 *
 *
 * Tile supports 2 buildings.
 */
class Evergreen : public TileBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Evergreen() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Evergreen(const Coordinate& location,
           const std::shared_ptr<iGameEventHandler>& eventhandler,
           const std::shared_ptr<iObjectManager>& objectmanager,
           const unsigned int& max_build = 1,
           const unsigned int& max_work = 13,
           const ResourceMap& production = ConstResources::EVERGREEN_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Evergreen() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Adds a new building-object to the tile. Building in Evergreen adds
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

}; // class Evergreen

} // namespace Course


#endif // Evergreen_H
