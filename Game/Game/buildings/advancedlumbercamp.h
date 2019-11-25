#ifndef AdvancedLumberCamp_H
#define AdvancedLumberCamp_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The AdvancedLumberCamp class represents a player's AdvancedLumberCamp-building.
 *
 * generates a large amount of wood per turn
 * requires a lot of resources to build
 * can only be built on forest tile
 *
 *
 */
class AdvancedLumberCamp : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    AdvancedLumberCamp() = delete;

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
    explicit AdvancedLumberCamp(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::A_LUMBERCAMP_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::A_LUMBERCAMP_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~AdvancedLumberCamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Lumber camp can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class AdvancedLumberCamp


#endif // AdvancedLumberCamp_H
