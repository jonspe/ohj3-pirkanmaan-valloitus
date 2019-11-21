#ifndef OreMine_H
#define OreMine_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The OreMine class represents a player's OreMine-building.
 *
 * Can be constructed on any stone-based tile (Stone, Ore, Diamond). \n
 * Production:
 * 5 stone
 * 2 ore
 *
 */
class OreMine : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    OreMine() = delete;

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
    explicit OreMine(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::ORE_MINE_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::ORE_MINE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~OreMine() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief OreMine can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class OreMine


#endif // OreMine_H
