#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H
#include "interfaces/iobjectmanager.h"
#include <vector>


namespace Course{
class ObjectManager : public iObjectManager
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
    void addTiles(const std::vector<std::shared_ptr<TileBase>>& tiles) override;

    /**
     * @brief Returns a shared pointer to a Tile that has specified coordinate.
     * @param coordinate Requested Tile's Coordinate
     * @return a pointer to a Tile that has the given coordinate.
     * If no for the coordinate exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
    std::shared_ptr<TileBase> getTile(const Coordinate& coordinate) override;

    /**
     * @brief Returns a shared pointer to a Tile that has specified ID
     * @param id Tile's ObjectId.
     * @return a pointer to the Tile that has the given ID
     * If no for the id exists, return empty pointer.
     * @post Exception Guarantee: Basic
     */
     std::shared_ptr<TileBase> getTile(const ObjectId& id) override;

    /**
     * @brief Returns a vector of shared pointers to Tiles specified by
     * a vector of Coordinates.
     * @param coordinates a vector of Coordinates for the requested Tiles
     * @return Vector of that contains pointers to Tile's that match
     * the coordinates. The vector is empty if no matches were made.
     * @post Exception Guarantee: Basic
     */
    std::vector<std::shared_ptr<TileBase>> getTiles(const std::vector<Coordinate>& coordinates) override;


private:
   std::vector<std::shared_ptr<Course::TileBase>> managed_tiles; // stores all currently managed tiles
   std::vector<std::shared_ptr<Course::TileBase>> wanted_tiles; // used in GetTiles, always cleared before calling
};

}
#endif // OBJECTMANAGER_H
