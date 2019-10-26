#ifndef GRASS_H
#define GRASS_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"

namespace Course {

/**
 * @brief The Grass class represents Grass in the gameworld.
 *
 * Grass has BasicProduction: \n
 * * Money = 2
 * * Food = 5
 * * Wood = 1
 * * Stone = 1
 * * Ore = 0
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Grass : public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Grass() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Grass(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const ResourceMap& production = ConstResources::GRASS_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Grass() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Grass

} // namespace Course


#endif // Grass_H
