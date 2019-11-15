#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H
#include "interfaces/igameeventhandler.h"
#include "Game/core/player.h"
#include "Game/workers/citizen.h"
#include "Game/workers/educatedcitizen.h"
#include "Game/core/objectmanager.h"
#include <map>

class GameEventHandler : public Course::iGameEventHandler
{
public:
    GameEventHandler();

    /**
     * @brief Modify Player's resources. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified.
     * @param resources ResourceMap containing change amounts.
     * @return
     * True - Modification was succesful.
     * False - Modification was succesful.
     */
    bool modifyResources(std::shared_ptr<Course::PlayerBase> player,
                                 Course::ResourceMap resources);

    /**
     * @brief Modify Player's specific resource. Can be used to both sum or subtract
     * @param player Pointer to the Player whose resources are being modified
     * @param resource BasicResource of resourcetype being modified
     * @param amount int of amount to change
     * @return
     * True - Modification was succesful.
     * False - Modification was succesful.
     */
    bool modifyResource(std::shared_ptr<Course::PlayerBase> player,
                                Course::BasicResource resource,
                                int amount);


    /**
     * @brief set player's resources to default values
     * @param player Pointer to the Player whose resources are being modified
     */
    void setPresetResources(std::shared_ptr<Course::PlayerBase> player);

    /**
     * @brief return given player's resources in a map
     * @param player Pointer to the Player whose resources are being modified
     */

    Course::ResourceMap getResources(std::shared_ptr<Course::PlayerBase> player);

    void addWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::PlayerBase> player, std::shared_ptr<Course::WorkerBase> worker_type);

    void addBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::PlayerBase> player, std::shared_ptr<Course::BuildingBase> building_type);

private:

    std::map<std::shared_ptr<Course::PlayerBase>,Course::ResourceMap> player_resources;

};

#endif // GAMEEVENTHANDLER_H
