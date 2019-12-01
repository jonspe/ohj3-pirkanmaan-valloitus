#include "mapgenerator.h"
#include "Game/tiles/elevatedtilebase.h"
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QTime>
#include <QDebug>

namespace {
    int roundToNearestMultiple(int value, int multiple)
    {
        return ((value + multiple/2) / multiple) * multiple;
    }
}




MapGenerator& MapGenerator::getInstance()
{
    static MapGenerator instance;
    return instance;
}

void MapGenerator::generateMap(int size_x, int size_y, unsigned int seed, const std::shared_ptr<Course::iObjectManager> &objectmanager, const std::shared_ptr<Course::iGameEventHandler> &eventhandler)
{
    // add constructors for every tile
    addConstructor<Animals>("Animals");
    addConstructor<Birch>("Birch");
    addConstructor<Diamond>("Diamond");
    addConstructor<Evergreen>("Evergreen");
    addConstructor<Grass>("Grass");
    addConstructor<Lake>("Lake");
    addConstructor<Ore>("Ore");
    addConstructor<Stone>("Stone");

    srand(seed);

    for (int x = 0; x < size_x; x++){
        for (int y = 0; y < size_y; y++){
           auto tile_coord = Course::Coordinate(x, y);

           m_tile_noise[tile_coord] = rand() % 100 + 1;
           m_forest_noise[tile_coord] = rand() % 100 + 1;
           m_stone_noise[tile_coord] = rand() % 100 + 1;
           m_tile_height[tile_coord] = rand() % 100 + 1;
        }
    }

    // invoke the gods
    for (int i = 0; i < 2; i++)
    {
        average(size_x, size_y);
    }

    srand(seed);

    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    for (int x = 0; x < size_x; ++x)
    {
        for (int y = 0; y < size_y; ++y)
        {
            ElevatedTileConstructorPointer ctor;
            Course::Coordinate coord(
                        static_cast<int>(x),
                        static_cast<int>(y));

            if (m_averaged_tile_noise[coord] < 45)
            {
                    ctor = m_all_ctors["Lake"];
                    // is lake, so set height to 0
                    m_averaged_tile_height[coord] = 0;
            }
            else if (m_averaged_stone_noise[coord] > 56)
            {
                int ore_roll = rand() %100+1;
                if (ore_roll > 96) {
                    ctor = m_all_ctors["Diamond"];
                } else if(ore_roll > 80) {
                    ctor = m_all_ctors["Ore"];
                } else {
                    ctor = m_all_ctors["Stone"];
                }
            }
            else if (m_averaged_forest_noise[coord] > 54)
            {
                    ctor = m_all_ctors["Birch"];
            }
            else if (m_averaged_forest_noise[coord] < 46)
            {
                    ctor = m_all_ctors["Evergreen"];
            }
            else
            {
                int animal_roll = rand() %100+1;
                if (animal_roll > 85){
                    ctor = m_all_ctors["Animals"];
                }
                else
                {
                    ctor = m_all_ctors["Grass"];
                }
            }

            // if not lake, increase intensity of height and step it up yo
            int height = m_averaged_tile_height[coord];
            if (height > 5)
            {
                m_averaged_tile_height[coord] = roundToNearestMultiple((height-35) * 3, 30);
            }

            tiles.push_back(ctor(coord - Course::Coordinate(size_x/2, size_y/2), m_averaged_tile_height[coord], eventhandler, objectmanager));
        }
    }
    objectmanager->addTiles(tiles);
}

void MapGenerator::average(int size_x, int size_y)
{
    for (int x = 0; x < size_x; x++){
        for (int y = 0; y < size_y; y++){

            std::set<Course::Coordinate> nearby_tiles;

            bool xplus = false;
            bool xminus = false;
            bool yplus = false;
            bool yminus = false;


            if (x + 1 < size_x){
                xplus = true;
            }
            if (x - 1 > 0){
                xminus = true;
            }
            if (y + 1 < size_y){
                yplus = true;
            }
            if (y - 1 > 0){
                yminus = true;
            }


            if (xplus){
                if (yplus){
                    Course::Coordinate nearby_tile_1 = Course::Coordinate(x + 1, y + 1);
                    nearby_tiles.insert(nearby_tile_1);
                }
                if (yminus){
                    Course::Coordinate nearby_tile_2 = Course::Coordinate(x + 1, y - 1);
                    nearby_tiles.insert(nearby_tile_2);
                }
                Course::Coordinate nearby_tile_3 = Course::Coordinate(x + 1, y );
                nearby_tiles.insert(nearby_tile_3);

            }

            if (yplus){
                    Course::Coordinate nearby_tile_4 = Course::Coordinate(x, y + 1);
                    nearby_tiles.insert(nearby_tile_4);
            }
            if (yminus){
                    Course::Coordinate nearby_tile_5 = Course::Coordinate(x + 1, y - 1);
                    nearby_tiles.insert(nearby_tile_5);
            }
            Course::Coordinate nearby_tile_6 = Course::Coordinate(x, y );
                    nearby_tiles.insert(nearby_tile_6);

            if (xminus){
                   if (yplus){
                       Course::Coordinate nearby_tile_7 = Course::Coordinate(x - 1, y + 1);
                       nearby_tiles.insert(nearby_tile_7);
                    }
                   if (yminus){
                       Course::Coordinate nearby_tile_8 = Course::Coordinate(x - 1, y - 1);
                       nearby_tiles.insert(nearby_tile_8);
                        }
                   Course::Coordinate nearby_tile_9 = Course::Coordinate(x - 1, y - 1);
                   nearby_tiles.insert(nearby_tile_9);
             }

            int sum = 0;
            int forest_sum = 0;
            int stone_sum = 0;
            int height_sum = 0;

            for (auto it = nearby_tiles.begin(); it != nearby_tiles.end(); it++){
                if ( m_tile_noise.find(*it) != m_tile_noise.end() && m_tile_average_count < 3) {
                    sum += m_tile_noise.at(*it);
                }
                if ( m_forest_noise.find(*it) != m_forest_noise.end()  && m_forest_average_count < 3) {
                    forest_sum += m_forest_noise.at(*it);
                }
                if ( m_stone_noise.find(*it) != m_stone_noise.end()  && m_stone_average_count < 4) {
                    stone_sum += m_stone_noise.at(*it);
                }
                if ( m_tile_height.find(*it) != m_tile_height.end()  && m_tile_height_average_count < 3) {
                    height_sum += m_tile_height.at(*it);
                }
            }

            int size = static_cast<int>(nearby_tiles.size());
            m_averaged_tile_noise[Course::Coordinate(x,y)] = int(sum / size);
            m_averaged_forest_noise[Course::Coordinate(x,y)] = int(forest_sum / size);
            m_averaged_stone_noise[Course::Coordinate(x,y)] = int(stone_sum / size);
            m_averaged_tile_height[Course::Coordinate(x,y)] = int(height_sum / size);
        }
    }

    m_tile_noise = m_averaged_tile_noise;
    m_forest_noise = m_averaged_forest_noise;
    m_stone_noise = m_averaged_stone_noise;
    m_tile_height = m_averaged_tile_height;

    m_tile_average_count++;
    m_forest_average_count++;
    m_stone_average_count++;
    m_tile_height_average_count++;
}

template<typename T>
void MapGenerator::addConstructor(std::string tile_type)
{
    ElevatedTileConstructorPointer ctor = std::make_shared<T, Course::Coordinate,
            int,
            std::shared_ptr<Course::iGameEventHandler>,
            std::shared_ptr<Course::iObjectManager> >;

    m_all_ctors[tile_type] = ctor;
}
