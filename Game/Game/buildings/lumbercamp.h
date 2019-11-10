#ifndef LUMBERCAMP_H
#define LUMBERCAMP_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The LumberCamp class represents a player's Lumbercamp-building.
 *
 * Can be constructed on any forested tile (Birch, Evergreen). \n
 * Production:
 * 9 wood
 *
 */
class LumberCamp : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    LumberCamp() = delete;

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
    explicit LumberCamp(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::LUMBERCAMP_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::LUMBERCAMP_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~LumberCamp() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Lumber camp can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

}; // class LumberCamp


#endif // Lumbercamp_H
