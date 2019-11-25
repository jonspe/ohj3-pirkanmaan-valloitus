#ifndef MARKETPLACE_H
#define MARKETPLACE_H


#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The Marketplace class represents a player's Marketplace-building.
 *
 * allows access to marketplace where resources can be traded
 * generates a small amount of gold
 * can only be built on grass
 *
 */
class Marketplace : public Course::BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Marketplace() = delete;

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
    explicit Marketplace(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::MARKETPLACE_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::MARKETPLACE_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Marketplace() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Marketplace can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;


    /**
     * @brief Access resource marketplace
     */
    void doSpecialAction() override;

}; // class Marketplace


#endif // Marketplace_H
