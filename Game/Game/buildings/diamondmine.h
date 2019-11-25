#ifndef DiamondMine_H
#define DiamondMine_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The DiamondMine class represents a player's DiamondMine-building.
 *
 * generates a ton of gold
 * can only be built on diamond tile
 *
 */
class DiamondMine : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    DiamondMine() = delete;

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
    explicit DiamondMine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::D_MINE_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::D_MINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~DiamondMine() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief DiamondMine can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class DiamondMine


#endif // DiamondMine_H
