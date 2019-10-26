#ifndef SAND_H
#define SAND_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"
namespace Course {

/**
 * @brief The Sand class represents Sand in the gameworld.
 *
 * Sand has BasicProduction: \n
 * * Money = 3
 * * Food = 2
 * * Wood = 0
 * * Stone = 2
 * * Ore = 0
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Sand : public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Sand() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Sand(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const ResourceMap& production = ConstResources::SAND_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Sand() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Sand

} // namespace Course


#endif // SAND_H
