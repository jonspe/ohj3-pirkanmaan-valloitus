#ifndef Farm_H
#define Farm_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


/**
 * @brief The Farm class represents a player's Farm-building.
 *
 * generates a small amount of food
 * can only be built on grass or animal tile
 */
class Farm : public Course::BuildingBase
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
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::FARM_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::FARM_PRODUCTION
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
     * @brief Farm can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class Farm


#endif // Farm_H
