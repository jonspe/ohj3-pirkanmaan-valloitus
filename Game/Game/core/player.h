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

    int happiness = 3;

};

#endif // PLAYER_H
