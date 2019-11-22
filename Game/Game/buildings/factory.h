#ifndef FACTORY_H
#define FACTORY_H



#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The Factory class represents a player's Factory-building.
 *
 * Can be constructed on any open land based tile. \n
 * Spends wood in return for gold
 * Production:
 * 5 gold
 *
 */
class Factory : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Factory() = delete;

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
    explicit Factory(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::FACTORY_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::FACTORY_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Factory() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Factory can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;


    /**
     * @brief Access resource Factory
     */

}; // class Factory

#endif // FACTORY_H
