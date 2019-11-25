#ifndef UNIVERSITY_H
#define UNIVERSITY_H

#include "buildings/buildingbase.h"
#include "Game/core/resources.h"

/**
 * @brief The University class represents a player's University-building.
 *
 * can be used to train educated citizens
 * generates some money and one ore
 * can only be built on grass
 *
 */
class University : public Course::BuildingBase
{    

public:
    /**
     * @brief Disabled parameterless constructor.
     */
    University() = delete;

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
    explicit University(
            const std::shared_ptr<Course::iGameEventHandler>& eventhandler,
            const std::shared_ptr<Course::iObjectManager>& objectmanager,
            const std::shared_ptr<Course::PlayerBase>& owner,
            const int& tilespaces = 1,
            const Course::ResourceMap& buildcost = ConstResources::UNIVERSITY_BUILD_COST,
            const Course::ResourceMap& production = ConstResources::UNIVERSITY_PRODUCTION
            );

    /**
     * @brief Default destructor.
     */
    virtual ~University() = default;

    /**
     * @copydoc GameObject::getType()
     */
    virtual std::string getType() const override;

    /**
     * @brief Trains an EducatedCitizen
     */
    virtual void doSpecialAction() override;

    /**
     * @brief University can only be built on a grass based hex
     */
    virtual bool canBePlacedOnTile(
            const std::shared_ptr<Course::TileBase> &target) const override;


}; // class University


#endif // University_H
