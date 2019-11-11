#ifndef PLAYER_H
#define PLAYER_H
#include "core/playerbase.h"
#include <vector>
#include "Game/core/resources.h"

class Player : public Course::PlayerBase
{
public:
    /**
     * @brief Constructor for the class
     * @param name A std::string for player's name
     * @param objects (optional) A std::vector of shared-pointers to
     * GameObjects.
     */
    Player(const std::string& name,
           const std::vector<std::shared_ptr<Course::GameObject> > objects ={});

    /**
     * @brief Default destructor
     */
    virtual ~Player() = default;

    /**
     * @brief Returns a ResourceMap with all of the player's resources
     */
    Course::ResourceMap getResources();

    /**
     * @brief Adds or subtracts from player's resources
     * @param modified_resources ResourceMap containing changed (positive) resource values
     * @param sign + or -, depending on if resources are being added or subtracted
     *
     * Example calls: players["1"]->modifyResources(ConstResources::FARM_BUILD_COST, "-");
     *                players["1"]->modifyResources(ConstResources::FARM_PRODUCTION, "+");
     */
    void modifyResources(Course::ResourceMap modified_resources, std::string sign);


    /**
     * @brief Returns player's happiness value
     */
    int getHappiness();


    /**
     * @brief Modifies player's happiness value
     * @param happiness_change Amount of happiness being modified in Int
     */
    void modifyHappiness(int happiness_change);

private:
    std::string m_name;
    std::vector<std::weak_ptr<Course::GameObject> > m_objects;

    Course::ResourceMap resource_stockpile = {
        {Course::BasicResource::MONEY, 200},
        {Course::BasicResource::FOOD, 200},
        {Course::BasicResource::WOOD, 200},
        {Course::BasicResource::STONE, 100},
        {Course::BasicResource::ORE, 0}

    };

    int happiness = 3;

};

#endif // PLAYER_H
