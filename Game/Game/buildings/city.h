#ifndef City_H
#define City_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


/**
 * @brief The City class represents a player's City-building.
 *
 * cannot be manually built, player gets one at the start of the game
 * claims nearby tiles in a radius of 2
 * allows training of basic citizens
 * generates some base resources to help player start off
 * only spawns on grass or forest
 *
 */
class City : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    City() = delete;

    /**
     * @brief Constructor for the class.
     *
     * @param eventhandler points to the student's GameEventHandler.
     * @param owner points to the owning player.
     * @param tile points to the tile upon which the building is constructed.
     *
     * @post Exception Guarantee: No guarantee.
     * @exception OwnerConflict - if the building conflicts with tile's
     * ownership.
     */
    explicit City(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::CITY_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::CITY_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~City() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Sets neighbouring Tiles' ownership to this building's
     * ownership in 3 tile-radius, if the Tiles don't already have an owner.
     * @post Exception guarantee: Basic
     */
    virtual void onBuildAction() override;

    /**
     * @brief Trains a normal citizen on the city tile
     */
    virtual void doSpecialAction() override;


}; // class City



#endif // City_H
