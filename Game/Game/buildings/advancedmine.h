#ifndef AdvancedMine_H
#define AdvancedMine_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The AdvancedMine class represents a player's AdvancedMine-building.
 *
 * generates a large amount of stone and some ore per turn
 * requires a lot of resources to build
 * can only be built on stone
 *
 *
 */
class AdvancedMine : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    AdvancedMine() = delete;

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
    explicit AdvancedMine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::A_MINE_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::A_MINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~AdvancedMine() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief AdvancedMine can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class AdvancedMine


#endif // AdvancedMine_H
