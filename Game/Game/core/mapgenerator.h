#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H
#include "core/worldgenerator.h"
#include "Game/tiles/animals.h"
#include "Game/tiles/birch.h"
#include "Game/tiles/diamond.h"
#include "Game/tiles/evergreen.h"
#include "Game/tiles/grass.h"
#include "Game/tiles/lake.h"
#include "Game/tiles/ores.h"
#include "Game/tiles/stone.h"


using ElevatedTileConstructorPointer = std::function<std::shared_ptr<ElevatedTileBase>(
    Course::Coordinate,
    int,
    std::shared_ptr<Course::iGameEventHandler>,
    std::shared_ptr<Course::iObjectManager>)>;

class MapGenerator
{
    /**
     * @brief The MapGenerator class is a singleton for generating tiles
     * for the game.
     *
     * Students use this to create new Tile-objects that form the gameworld. \n
     * Usage:
     * 1. Use MapGenerator::getInstance() to get a reference to the singleton.
     * 2. Call addConstructor with each Tile type you created.
     * 3. Generate the map through the reference.
     */

    public:
        /**
         * @brief Used to get a reference to the Singleton instance.
         * @return Reference to the Singleton instance.
         * @post Exception guarantee: No-throw
         */
        static MapGenerator& getInstance();
        // Prevent copy and move construction and assignment.
        MapGenerator(const MapGenerator&) = delete;
        MapGenerator& operator=(const MapGenerator&) = delete;
        MapGenerator(MapGenerator&&) = delete;
        MapGenerator& operator=(MapGenerator&&) = delete;

        /**
         * @brief Register a Tile's constructor for use in map generation.
         * @note Do this only once per Tile type or they won't be equally common.
         * Use the Tile's type as the template parameter: addConstructor<Forest>();
         * @param weight represents the rarity of the Tile, high being common.
         */
        template<typename T>
        void addConstructor(std::string tile_type);

        /**
         * @brief Generates Tile-objects and sends them to ObjectManager.
         * @param size_x is the horizontal size of the map area.
         * @param size_y is the vertical size of the map area.
         * @param seed is the seed-value used in the generation.
         * @param objectmanager points to the ObjectManager that receives the
         * generated Tiles.
         * @param eventhandler points to the student's GameEventHandler.
         * @post Exception guarantee: No-throw
         */
        void generateMap(int size_x,
                         int size_y,
                         unsigned int seed,
                         const std::shared_ptr<Course::iObjectManager>& objectmanager,
                         const std::shared_ptr<Course::iGameEventHandler>& eventhandler);


    private:
        /**
         * @brief Default constructor.
         */
        MapGenerator() = default;
        /**
         * @brief Default destructor.
         */
        ~MapGenerator() = default;

        /**
         * @brief averages tile properties of world gen map
         * @param size_x
         * @param size_y
         */
        void average(int size_x, int size_y);

        // For mapping constructors.
        std::map<std::string, ElevatedTileConstructorPointer> m_all_ctors;
        std::map<Course::Coordinate, int> m_averaged_tile_noise;
        std::map<Course::Coordinate, int> m_averaged_forest_noise;
        std::map<Course::Coordinate, int> m_averaged_stone_noise;
        std::map<Course::Coordinate, int> m_averaged_tile_height;

        std::map<Course::Coordinate, int> m_tile_noise;
        std::map<Course::Coordinate, int> m_forest_noise;
        std::map<Course::Coordinate, int> m_stone_noise;
        std::map<Course::Coordinate, int> m_tile_height;

        int m_tile_average_count = 0;
        int m_forest_average_count = 0;
        int m_stone_average_count = 0;
        int m_tile_height_average_count = 0;
 }; // class MapGenerator


#endif // MAPGENERATOR_H
