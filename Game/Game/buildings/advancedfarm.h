#ifndef AdvancedFarm_H
#define AdvancedFarm_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


/**
 * @brief The AdvancedFarm class represents a player's AdvancedFarm-building.
 *
 * generates a large amount of food per turn
 * requires a lot of resources to build
 * can only be built on grass or animal tile
 *
 *
 */
class AdvancedFarm : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    AdvancedFarm() = delete;

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
    explicit AdvancedFarm(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::A_FARM_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::A_FARM_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~AdvancedFarm() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief AdvancedFarm can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class AdvancedFarm


#endif // AdvancedFarm_H
