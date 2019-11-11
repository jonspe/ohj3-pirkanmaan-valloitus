#include "mapgenerator.h"
#include <iostream>
#include <set>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <QTime>

MapGenerator& MapGenerator::getInstance()
{
    static MapGenerator instance;
    return instance;
}

void MapGenerator::generateMap(unsigned int size_x, unsigned int size_y, unsigned int seed, const std::shared_ptr<Course::iObjectManager> &objectmanager, const std::shared_ptr<Course::iGameEventHandler> &eventhandler)
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
           tile_noise[tile_coord] = rand() % 100 + 1;
           forest_noise[tile_coord] = rand() % 100 + 1;
           stone_noise[tile_coord] = rand() % 100 + 1;
           tile_height[tile_coord] = rand() % 100 + 1;
        }
    }
    // invoke the gods
    average(size_x,size_y);
    average(size_x,size_y);
    average(size_x,size_y);

    srand(seed);
    std::vector<std::shared_ptr<Course::TileBase>> tiles;
    for (unsigned int x = 0; x < size_x; ++x)
    {
        for (unsigned int y = 0; y < size_y; ++y)
        {
            Course::TileConstructorPointer ctor;
            if(averaged_tile_noise[Course::Coordinate(x,y)] < 45){
                    ctor = all_ctors["Lake"];

            }else if(averaged_stone_noise[Course::Coordinate(x,y)] > 56){
                    int ore_roll = rand() %100+1;
                    if (ore_roll > 96){
                        ctor = all_ctors["Diamond"];
                    }else if(ore_roll > 80){
                        ctor = all_ctors["Ore"];
                    }else{
                        ctor = all_ctors["Stone"];
                    }

            }else if(averaged_forest_noise[Course::Coordinate(x,y)] > 54){
                    ctor = all_ctors["Birch"];
            }else if(averaged_forest_noise[Course::Coordinate(x,y)] < 46){
                    ctor = all_ctors["Evergreen"];

            }else{
                    int animal_roll = rand() %100+1;
                    if (animal_roll > 85){
                        ctor = all_ctors["Animals"];
                    }else{
                        ctor = all_ctors["Grass"];
            }


        } tiles.push_back(ctor(Course::Coordinate(x, y), eventhandler, objectmanager));
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
            std::set<Course::Coordinate>::iterator it = nearby_tiles.begin();
            for (it ; it != nearby_tiles.end(); it++){
                if ( tile_noise.find(*it) != tile_noise.end() && tile_average_count < 3) {
                       sum += tile_noise.at(*it);
                 }
                if ( forest_noise.find(*it) != forest_noise.end()  && forest_average_count < 3) {
                       forest_sum += forest_noise.at(*it);
                 }
                if ( stone_noise.find(*it) != stone_noise.end()  && stone_average_count < 4) {
                       stone_sum += stone_noise.at(*it);

                 }
                if ( tile_height.find(*it) != tile_height.end()  && tile_height_average_count < 3) {
                       height_sum += tile_height.at(*it);

                 }

            }


           averaged_tile_noise[Course::Coordinate(x,y)] = int(sum / nearby_tiles.size());
           averaged_forest_noise[Course::Coordinate(x,y)] = int(forest_sum / nearby_tiles.size());
           averaged_stone_noise[Course::Coordinate(x,y)] = int(stone_sum / nearby_tiles.size());
           averaged_tile_height[Course::Coordinate(x,y)] = int(height_sum / nearby_tiles.size());

        }

    }

    tile_noise = averaged_tile_noise;
    forest_noise = averaged_forest_noise;
    stone_noise = averaged_stone_noise;
    tile_height = averaged_tile_height;

    tile_average_count++;
    forest_average_count++;
    stone_average_count++;
    tile_height_average_count++;

}

std::map<Course::Coordinate, int> MapGenerator::getHeight()
{
    return averaged_tile_height;
}

MapGenerator::MapGenerator()
{

}

MapGenerator::~MapGenerator()
{

}


template<typename T>
void MapGenerator::addConstructor(std::string tile_type)
{
    Course::TileConstructorPointer ctor = std::make_shared<T, Course::Coordinate,
            std::shared_ptr<Course::iGameEventHandler>,
            std::shared_ptr<Course::iObjectManager> >;

    all_ctors[tile_type] = ctor;


}
