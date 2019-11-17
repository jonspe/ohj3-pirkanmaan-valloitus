#ifndef PLAYER_H
#define PLAYER_H
#include "core/playerbase.h"
#include <vector>
#include "Game/core/resources.h"
#include "Game/core/objectmanager.h"

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
     * @brief generate resources for every claimed tile and building
     * @param object_manager pointer to main object manager
     */

    void generateResources(std::shared_ptr<ObjectManager> object_manager);


private:
    std::string m_name;
    std::vector<std::weak_ptr<Course::GameObject> > m_objects;


};

#endif // PLAYER_H
