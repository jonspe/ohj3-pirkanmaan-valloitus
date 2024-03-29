#ifndef VICTORYMONUMENT_H
#define VICTORYMONUMENT_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The VictoryMonument class represents a player's VictoryMonument-building.
 *
 * can only be built on grass
 * first player to build it wins the game
 * demolish button replaced with end game button
 *
 */
class VictoryMonument : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    VictoryMonument() = delete;

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
    explicit VictoryMonument(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::VICTORYMONUMENT_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::VICTORYMONUMENT_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~VictoryMonument() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief VictoryMonument can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;

    /**
     * @brief Sets builder as winner and stores current turn;
     */
    virtual void onBuildAction() override;

}; // class VictoryMonument


#endif // VictoryMonument_H
