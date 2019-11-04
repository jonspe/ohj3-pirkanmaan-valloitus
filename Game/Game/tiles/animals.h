#ifndef Animals_H
#define Animals_H

#include "tiles/tilebase.h"
#include "Game/core/resources.h"

/**
 * @brief The Animals class represents Animals in the gameworld.
 *
 * Animals has BasicProduction: \n
 * * Money = 4
 * * Food = 9
 * * Wood = 1
 * * Stone = 1
 * * Ore = 0
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Animals : public Course::TileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Animals() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Animals(const Course::Coordinate& location,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production = ConstResources::ANIMALS_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Animals() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Animals



#endif // Animals_H
