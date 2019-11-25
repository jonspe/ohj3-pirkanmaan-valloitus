#ifndef Animals_H
#define Animals_H

#include "Game/tiles/elevatedtilebase.h"
#include "Game/core/resources.h"

/**
 * @brief The Animals class represents Animals in the gameworld.
 *
 * generates a lot of food and gold
 *
 */
class Animals : public ElevatedTileBase
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
              const int& height,
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
