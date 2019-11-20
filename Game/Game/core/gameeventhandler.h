#ifndef GAMEEVENTHANDLER_H
#define GAMEEVENTHANDLER_H
#include "interfaces/igameeventhandler.h"
#include "Game/core/player.h"
#include "Game/workers/citizen.h"
#include "Game/workers/educatedcitizen.h"
#include "Game/core/objectmanager.h"
#include "Game/core/marketplacetrader.h"
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


    void tilePressed(std::shared_ptr<Course::TileBase> &tile);

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

    void setPlayers(std::map<std::string, std::shared_ptr<Player>> player_map);

    /**
     * @brief adds a new worker to tile at given coordinate
     * @param location coordinate of tile where worker spawns
     * @param object_manager pointer to main object manager
     * @param worker_type pointer to type of worker being added (Citizen, EducatedCitizen)
     */
    void addWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::WorkerBase> worker_type);
    /**
     * @brief removes a worker from tile at given coordinate
     * @param location coordinate of tile where worker is kill
     * @param object_manager pointer to main object manager
     * @param worker_type pointer to type of worker being removed (Citizen, EducatedCitizen)
     */
    void removeWorker(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::WorkerBase> worker_type);
    /**
     * @brief adds a new building to tile at given coordinate
     * @param location coordinate of tile where building spawns
     * @param object_manager pointer to main object manager
     * @param building_type pointer to type of building being added (Mine, University etc)
     */
    void addBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> building_type);
    /**
     * @brief removes a new building from tile at given coordinate
     * @param location coordinate of tile where building is removed
     * @param object_manager pointer to main object manager
     * @param building_type pointer to type of building being removed (Mine, University etc)
     */

    void removeBuilding(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> building_type);

    /**
     * @brief claims tile at given coordinate to given player
     * @param location coordinate of tile where worker spawns
     * @param object_manager pointer to main object manager
     */
    void claimTile(Course::Coordinate location, std::shared_ptr<ObjectManager> object_manager);

    /**
     * @brief spawns city in map quadrant for every player
     * @param map_size size of map
     * @param current_player id of current player
     * @param object_manager pointer to main object manager
     * @param players vector of all players
     * @param new_city pointer to City building)
     */

    void firstTurn(unsigned int map_size, std::shared_ptr<ObjectManager> object_manager, std::shared_ptr<Course::BuildingBase> new_city);


    std::tuple<unsigned int, unsigned int> passTurn(unsigned int player_amount);



    /**
     * @brief returns MarketplaceTrader object
     */
    MarketplaceTrader getTrader();

    /**
     * @brief player buys 100 of resource
     * @param resource resource being bought
     * @param player pointer to player using marketplace
     */
    void resourceBought(std::shared_ptr<Player> player, Course::BasicResource resource);


    /**
     * @brief player sells 100 of resource
     * @param resource resource being sold
     * @param player pointer to player using marketplace
     */
    void resourceSold(std::shared_ptr<Player> player, Course::BasicResource resource);


private:

    std::map<std::shared_ptr<Course::PlayerBase>,Course::ResourceMap> player_resources; // contains resources of every player
    MarketplaceTrader trader;

    unsigned int turn = 1;
    unsigned int current_player = 0;

    std::map<std::string, std::shared_ptr<Player>> players;

};

#endif // GAMEEVENTHANDLER_H
