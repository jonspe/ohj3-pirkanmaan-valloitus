#ifndef Colony_H
#define Colony_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"


namespace Course {


/**
 * @brief The Colony class represents a player's Colony-building.
 *
 * It can be constructed on any claimed tile with a free space. \n
 * Effects: Claims surrounding unclaimed tiles. \n
 * Radius: 2 tiles\n
 *
 */
class Colony : public BuildingBase
{
public:
    /**
     * @brief Disabled parameterless constructor.
     */
    Colony() = delete;

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
    explicit Colony(
            const std::shared_ptr<iGameEventHandler>& eventhandler,
            const std::shared_ptr<iObjectManager>& objectmanager,
            const std::shared_ptr<PlayerBase>& owner,
            const int& tilespaces = 1,
            const ResourceMap& buildcost = ConstResources::COLONY_BUILD_COST,
            const ResourceMap& production = ConstResources::COLONY_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~Colony() = default;

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


}; // class Colony

} // namespace Course


#endif // Colony_H
