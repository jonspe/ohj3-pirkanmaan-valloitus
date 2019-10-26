#ifndef ORE_H
#define ORE_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"
namespace Course {

/**
 * @brief The Ore class represents Ore in the gameworld.
 *
 * Ore has BasicProduction: \n
 * * Money = 1
 * * Food = 0
 * * Wood = 0
 * * Stone = 5
 * * Ore = 5
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Ore : public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Ore() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Ore(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const ResourceMap& production = ConstResources::ORE_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Ore() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Ore

} // namespace Course


#endif // Ore_H
