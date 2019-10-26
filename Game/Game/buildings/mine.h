#ifndef Mine_H
#define Mine_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


namespace Course {


/**
 * @brief The Mine class represents a player's Mine-building.
 *
 * Can be constructed on any stone-based tile (Stone, Ore, Diamond). \n
 * Production:
 * 5 stone
 * 2 ore
 *
 */
class Mine : public BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Mine() = delete;

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
    explicit Mine(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const int& tilespaces = 1,
            const ResourceMap& buildcost = ConstResources::MINE_BUILD_COST,
            const ResourceMap& production = ConstResources::MINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Mine() = default;

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
     * @brief Mine can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<TileBase> &target) const override;

}; // class Mine

} // namespace Course


#endif // Mine_H
