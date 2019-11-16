#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "interfaces/iobjectmanager.h"
#include "Game/tiles/elevatedtilebase.h"

#include <vector>


class ObjectManager : public Course::iObjectManager
{
public:
    ObjectManager();

    /**
     * @brief Adds new tiles to the ObjectManager.
     * @param tiles a vector that contains the Tiles to be added.
     * @post The tile-pointers in the vector are stored in the ObjectManager.
     * Exception Guarantee: Basic
     *
     */
    void addTiles(const std::vector<std::shared_ptr<Course::TileBase>>& tiles) override;

    /**
     * @brief Returns a shared pointer to a Tile that has specified coordinate.
     * @param coordinate Requested Tile's Coordinate
     * @return a pointer to a Tile that has the given coordinate.
     * If no for the coordinate exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<Course::TileBase> getTile(const Course::Coordinate& coordinate) override;

    /**
     * @brief Returns a shared pointer to a Tile that has specified ID
     * @param id Tile's ObjectId.
     * @return a pointer to the Tile that has the given ID
     * If no for the id exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
     std::shared_ptr<Course::TileBase> getTile(const Course::ObjectId& id) override;

    /**
     * @brief Returns a vector of shared pointers to Tiles specified by
     * a vector of Coordinates.
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector of that contains pointers to Tile's that match
     * the coordinates. The vector is empty if no matches were made.
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<Course::TileBase>> getTiles(const std::vector<Course::Coordinate>& coordinates) override;

    /**
     * @brief Returns a vector of shared pointers to all Tiles
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector that contains pointers to all Tiles
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<Course::TileBase>> getAllTiles();

    /**
     * @brief stores pointer to building in a vector so the weak_ptr doesnt commit seppuku
     * @param building pointer to newly built building
     */
    void addBuilding(std::shared_ptr<Course::BuildingBase> building);
    /**
     * @brief stores pointer to worker in a vector so the weak_ptr doesnt commit seppuku
     * @param building pointer to newly built worker
     */
    void addWorker(std::shared_ptr<Course::WorkerBase> worker);

    //std::shared_ptr<ElevatedTileBase> getElevatedTile(const Course::Coordinate& coordinate);
    //std::shared_ptr<ElevatedTileBase> getElevatedTile(const Course::ObjectId& id);
    //std::vector<std::shared_ptr<ElevatedTileBase>> getElevatedTiles(const std::vector<Course::Coordinate>& coordinates);
    //std::vector<std::shared_ptr<ElevatedTileBase>> getAllElevatedTiles();

private:
    std::vector<std::shared_ptr<Course::TileBase>> tile_data; // stores all currently managed tiles
    std::vector<std::shared_ptr<Course::BuildingBase>> buildings; // stores weak pointers so they dont kill themselves
    std::vector<std::shared_ptr<Course::WorkerBase>> workers; // stores weak pointers so they dont kill themselves
};

#endif // OBJECTMANAGER_H
