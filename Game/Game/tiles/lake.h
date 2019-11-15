#ifndef LAKE_H
#define LAKE_H

#include "Game/tiles/elevatedtilebase.h"
#include "Game/core/resources.h"

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
class Lake : public ElevatedTileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
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
    Lake(const Course::Coordinate& location,
              const int& height,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 0,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production = ConstResources::LAKE_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Lake() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Lake

#endif // Lake_H
