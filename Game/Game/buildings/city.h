#ifndef City_H
#define City_H

#include "buildings/buildingbase.h"
#include "core/resources.h"


namespace Course {

/**
 * @brief The City class represents a player's City-building.
 *
 * It can be constructed on any tile that has not been claimed by any other
 * player. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 3 tiles.
 */
class City : public BuildingBase
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
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const int& tilespaces = 1,
            const ResourceMap& buildcost = ConstResources::CITY_BUILD_COST,
            const ResourceMap& production = ConstResources::CITY_PRODUCTION
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

}; // class City

} // namespace Course


#endif // City_H
