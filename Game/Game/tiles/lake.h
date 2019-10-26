#ifndef LAKE_H
#define LAKE_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"


namespace Course {

/**
 * @brief The Lake class represents Lake in the gameworld.
 *
 * Lake has BasicProduction: \n
 * * Money = 5
 * * Food = 5
 * * Wood = 0
 * * Stone = 0
 * * Ore = 0
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Lake : public TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Lake() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Lake(const Coordinate& location,
              const std::shared_ptr<iGameEventHandler>& eventhandler,
              const std::shared_ptr<iObjectManager>& objectmanager,
              const unsigned int& max_build = 0,
              const unsigned int& max_work = 1,
              const ResourceMap& production = ConstResources::LAKE_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Lake() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Lake

} // namespace Course


#endif // Lake_H
