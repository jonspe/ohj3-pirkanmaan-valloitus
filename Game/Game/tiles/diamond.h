#ifndef Diamond_H
#define Diamond_H

#include "Game/tiles/elevatedtilebase.h"
#include "Game/core/resources.h"

/**
 * @brief The Diamond class represents Diamond in the gameworld.
 *
 * generates a lot of gold and some stone
 */
class Diamond : public ElevatedTileBase
{
public:
    static const unsigned int MAX_BUILDINGS;
    static const unsigned int MAX_WORKERS;
    static const Course::ResourceMap BASE_PRODUCTION;
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
    Diamond(const Course::Coordinate& location,
              const int& height,
              const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
              const std::shared_ptr<Course::iObjectManager>& objectmanager,
              const unsigned int& max_build = 1,
              const unsigned int& max_work = 1,
              const Course::ResourceMap& production = ConstResources::DIAMOND_BP);

    /**
     * @brief Default destructor.
     */
    virtual ~Diamond() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

}; // class Diamond



#endif // Diamond_H
