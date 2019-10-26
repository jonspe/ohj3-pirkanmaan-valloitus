#ifndef Diamond_H
#define Diamond_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"

namespace Course {

/**
 * @brief The Diamond class represents Diamond in the gameworld.
 *
 * Diamond has BasicProduction: \n
 * * Money = 15
 * * Food = 0
 * * Wood = 0
 * * Stone = 5
 * * Ore = 1
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Diamond : public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Diamond() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Diamond(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const ResourceMap& production = ConstResources::DIAMOND_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Diamond() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Diamond

} // namespace Course


#endif // Diamond_H
