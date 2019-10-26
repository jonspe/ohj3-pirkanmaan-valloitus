#ifndef RESOURCES_H
#define RESOURCES_H

#include "core\basicresources.h"

namespace Course {

namespace ConstResources {

const ResourceMap EMPTY = {};

// Building - Farm
const ResourceMap FARM_BUILD_COST = {
    {BasicResource::MONEY, 50},
    {BasicResource::FOOD, 100},
    {BasicResource::WOOD, 25}
};
const ResourceMap FARM_PRODUCTION = {
    {BasicResource::MONEY, 1},
    {BasicResource::FOOD, 5}
};


// Building - City
const ResourceMap CITY_BUILD_COST = {
    {BasicResource::MONEY, 750},
    {BasicResource::FOOD, 1000},
    {BasicResource::WOOD, 500},
    {BasicResource::STONE, 250}
};
const ResourceMap CITY_PRODUCTION = {
    {BasicResource::MONEY, 10},
    {BasicResource::FOOD, -4},
};


// Building - COLONY
const ResourceMap COLONY_BUILD_COST = {
    {BasicResource::MONEY, 150},
    {BasicResource::FOOD, 400},
    {BasicResource::WOOD, 200},
    {BasicResource::STONE, 25}
};

const ResourceMap COLONY_PRODUCTION = {
    {BasicResource::MONEY, 5},
    {BasicResource::FOOD, -2}
};


// Worker - BasicWorker
const ResourceMapDouble BW_WORKER_EFFICIENCY = {
    {MONEY, 0.25},
    {FOOD, 1.00},
    {WOOD, 0.75},
    {STONE, 0.50},
    {ORE, 0.50}
};

const ResourceMap BW_RECRUITMENT_COST = {
    {MONEY, 10},
    {FOOD, 25}
};


const ResourceMap BIRCH_BP = {
    {MONEY, 1},
    {FOOD, 3},
    {WOOD, 5},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap EVERGREEN_BP = {
    {MONEY, 1},
    {FOOD, 2},
    {WOOD, 6},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap GRASS_BP = {
    {MONEY, 2},
    {FOOD, 5},
    {WOOD, 1},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap ANIMALS_BP = {
    {MONEY, 4},
    {FOOD, 9},
    {WOOD, 1},
    {STONE, 1},
    {ORE, 0},
};

const ResourceMap STONE_BP = {
    {MONEY, 1},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 5},
    {ORE, 1},
};

const ResourceMap SAND_BP = {
    {MONEY, 3},
    {FOOD, 2},
    {WOOD, 0},
    {STONE, 2},
    {ORE, 0},
};

const ResourceMap DIAMOND_BP = {
    {MONEY, 15},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 5},
    {ORE, 1},
};

const ResourceMap ORE_BP = {
    {MONEY, 0},
    {FOOD, 0},
    {WOOD, 0},
    {STONE, 5},
    {ORE, 5},
};

const ResourceMap LAKE_BP = {
    {MONEY, 5},
    {FOOD, 5},
    {WOOD, 0},
    {STONE, 0},
    {ORE, 0},
};

}
}
#endif // RESOURCES_H
