#ifndef Stone_H
#define Stone_H

#include "Game/tiles/elevatedtilebase.h"
#include "Game/core/resources.h"

/**
 * @brief The Stone class represents Stone in the gameworld.
 *
 * Stone has BasicProduction: \n
 * * Money = 1
 * * Food = 0
 * * Wood = 0
 * * Stone = 5
 * * Ore = 1
 *
 * Functionality follows mainly the parent class' functionality.
 *
 * Tile supports 3 buildings.
 */
class Stone : public ElevatedTileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
    /**
     * @brief Disabled parameterless constructor.
     */
    Stone() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param location is the Coordinate where the Tile is located in the game.
     * @param eventhandler points to the student's GameEventHandler.
     */
    Stone(const Course::Coordinate& location,
              const int& height,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production = ConstResources::STONE_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Stone() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Stone


#endif // Stone_H
