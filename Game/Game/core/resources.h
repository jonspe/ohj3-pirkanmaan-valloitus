#ifndef RESOURCES_H
#define RESOURCES_H

#include "core\basicresources.h"

namespace ConstResources {

const Course::ResourceMap EMPTY = {};



// Building - City
const Course::ResourceMap CITY_BUILD_COST = {
    {Course::BasicResource::MONEY, 750},
    {Course::BasicResource::FOOD, 1000},
    {Course::BasicResource::WOOD, 500},
    {Course::BasicResource::STONE, 250}
};
const Course::ResourceMap CITY_PRODUCTION = {
    {Course::BasicResource::MONEY, 10},
    {Course::BasicResource::FOOD, -4},
};


// Building - COLONY
const Course::ResourceMap COLONY_BUILD_COST = {
    {Course::BasicResource::MONEY, 150},
    {Course::BasicResource::FOOD, 400},
    {Course::BasicResource::WOOD, 200},
    {Course::BasicResource::STONE, 25}
};

const Course::ResourceMap COLONY_PRODUCTION = {
    {Course::BasicResource::MONEY, 5},
    {Course::BasicResource::FOOD, -2}
};

// Building - Farm
const Course::ResourceMap FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 25}
};
const Course::ResourceMap FARM_PRODUCTION = {
    {Course::BasicResource::MONEY, 1},
    {Course::BasicResource::FOOD, 5}
};

// Building - Mine
const Course::ResourceMap MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::FOOD, 100},
    {Course::BasicResource::WOOD, 25}
};
const Course::ResourceMap MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 5},
    {Course::BasicResource::ORE, 2}
};


// Worker - BasicWorker
const Course::ResourceMapDouble BW_WORKER_EFFICIENCY = {
    {Course::MONEY, 0.25},
    {Course::FOOD, 1.00},
    {Course::WOOD, 0.75},
    {Course::STONE, 0.50},
    {Course::ORE, 0.50}
};

const Course::ResourceMap BW_RECRUITMENT_COST = {
    {Course::MONEY, 10},
    {Course::FOOD, 25}
};


const Course::ResourceMap BIRCH_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 3},
    {Course::WOOD, 5},
    {Course::STONE, 1},
    {Course::ORE, 0},
};

const Course::ResourceMap EVERGREEN_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 2},
    {Course::WOOD, 6},
    {Course::STONE, 1},
    {Course::ORE, 0},
};

const Course::ResourceMap GRASS_BP = {
    {Course::MONEY, 2},
    {Course::FOOD, 5},
    {Course::WOOD, 1},
    {Course::STONE, 1},
    {Course::ORE, 0},
};

const Course::ResourceMap ANIMALS_BP = {
    {Course::MONEY, 4},
    {Course::FOOD, 9},
    {Course::WOOD, 1},
    {Course::STONE, 1},
    {Course::ORE, 0},
};

const Course::ResourceMap STONE_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 1},
};

const Course::ResourceMap SAND_BP = {
    {Course::MONEY, 3},
    {Course::FOOD, 2},
    {Course::WOOD, 0},
    {Course::STONE, 2},
    {Course::ORE, 0},
};

const Course::ResourceMap DIAMOND_BP = {
    {Course::MONEY, 15},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 1},
};

const Course::ResourceMap ORE_BP = {
    {Course::MONEY, 0},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 5},
    {Course::ORE, 5},
};

const Course::ResourceMap LAKE_BP = {
    {Course::MONEY, 5},
    {Course::FOOD, 5},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

}

#endif // RESOURCES_H
