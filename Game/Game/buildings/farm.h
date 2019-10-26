#ifndef Farm_H
#define Farm_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


namespace Course {


/**
 * @brief The Farm class represents a player's Farm-building.
 *
 * Can be constructed on any stone-based tile (Stone, Ore, Diamond). \n
 * Production:
 * 5 food
 * 1 money
 *
 */
class Farm : public BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Farm() = delete;

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
    explicit Farm(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const int& tilespaces = 1,
            const ResourceMap& buildcost = ConstResources::FARM_BUILD_COST,
            const ResourceMap& production = ConstResources::FARM_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Farm() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Sets neighbouring Tiles' ownership to this building's
     * ownership in 1 tile-radius, if the Tiles don't already have an owner.
     * @post Exception guarantee: Basic
     */
    virtual void onBuildAction() override;

    /**
     * @brief Farm can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<TileBase> &target) const override;

}; // class Farm

} // namespace Course


#endif // Farm_H
