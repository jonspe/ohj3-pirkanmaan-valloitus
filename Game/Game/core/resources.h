#ifndef RESOURCES_H
#define RESOURCES_H

#include "core/basicresources.h"

namespace ConstResources {

const Course::ResourceMap EMPTY = {};


// Building - City
const Course::ResourceMap CITY_BUILD_COST = {
    {Course::BasicResource::MONEY, 0},
    {Course::BasicResource::FOOD, 0},
    {Course::BasicResource::WOOD, 0},
    {Course::BasicResource::STONE, 0}
};
const Course::ResourceMap CITY_PRODUCTION = {
    {Course::BasicResource::MONEY, 25},
    {Course::BasicResource::WOOD, 2},
    {Course::BasicResource::FOOD, -5},
    {Course::BasicResource::STONE, 1},

};


// Building - COLONY
const Course::ResourceMap COLONY_BUILD_COST = {
    {Course::BasicResource::MONEY, -200},
    {Course::BasicResource::FOOD, -400},
    {Course::BasicResource::WOOD, -200},
    {Course::BasicResource::STONE, -100},
};

const Course::ResourceMap COLONY_PRODUCTION = {
    {Course::BasicResource::MONEY, -15},
    {Course::BasicResource::FOOD, -65}
};

// Building - Farm
const Course::ResourceMap FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, -60},
    {Course::BasicResource::WOOD, -80}
};
const Course::ResourceMap FARM_PRODUCTION = {
    {Course::BasicResource::MONEY, -2},
    {Course::BasicResource::FOOD, 7}
};

// Building - Advanced Farm
const Course::ResourceMap A_FARM_BUILD_COST = {
    {Course::BasicResource::MONEY, -300},
    {Course::BasicResource::WOOD, -250},
    {Course::BasicResource::ORE, -30}
};
const Course::ResourceMap A_FARM_PRODUCTION = {
    {Course::BasicResource::MONEY, -4},
    {Course::BasicResource::FOOD, 20}
};


// Building - Mine
const Course::ResourceMap MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, -100},
    {Course::BasicResource::WOOD, -80}
};
const Course::ResourceMap MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 6},
    {Course::BasicResource::ORE, 1},
    {Course::BasicResource::MONEY, -2}
};

// Building - Advanced Mine
const Course::ResourceMap A_MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, -200},
    {Course::BasicResource::WOOD, -100},
    {Course::BasicResource::STONE, -50},
    {Course::BasicResource::ORE, -20}

};
const Course::ResourceMap A_MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 20},
    {Course::BasicResource::ORE, 2},
    {Course::BasicResource::MONEY, -4}
};

// Building - Diamond Mine
const Course::ResourceMap D_MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, -200},
    {Course::BasicResource::WOOD, -150},
    {Course::BasicResource::ORE, -10}
};
const Course::ResourceMap D_MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 2},
    {Course::BasicResource::MONEY, 40}
};


// Building - Ore Mine
const Course::ResourceMap ORE_MINE_BUILD_COST = {
    {Course::BasicResource::MONEY, -150},
    {Course::BasicResource::WOOD, -120},
    {Course::BasicResource::STONE, -40}
};
const Course::ResourceMap ORE_MINE_PRODUCTION = {
    {Course::BasicResource::STONE, 2},
    {Course::BasicResource::ORE, 3},
    {Course::BasicResource::MONEY, -2}

};

// Building - Lumber Camp
const Course::ResourceMap LUMBERCAMP_BUILD_COST = {
    {Course::BasicResource::MONEY, -70},
    {Course::BasicResource::WOOD, -40}
};
const Course::ResourceMap LUMBERCAMP_PRODUCTION = {
    {Course::BasicResource::WOOD, 10},
    {Course::BasicResource::MONEY, -2}
};

// Building - Advanced Lumber Camp
const Course::ResourceMap A_LUMBERCAMP_BUILD_COST = {
    {Course::BasicResource::MONEY, -200},
    {Course::BasicResource::FOOD, -150},
    {Course::BasicResource::ORE, -20}
};
const Course::ResourceMap A_LUMBERCAMP_PRODUCTION = {
    {Course::BasicResource::WOOD, 30},
    {Course::BasicResource::MONEY, 4}
};

// Building - University
const Course::ResourceMap UNIVERSITY_BUILD_COST = {
    {Course::BasicResource::MONEY, -500},
    {Course::BasicResource::FOOD, -200},
    {Course::BasicResource::STONE, -300},
    {Course::BasicResource::ORE, -100}
};
const Course::ResourceMap UNIVERSITY_PRODUCTION = {
    {Course::BasicResource::MONEY, -10},
    {Course::BasicResource::ORE, 1}
};

// Building - Victory Monument
const Course::ResourceMap VICTORYMONUMENT_BUILD_COST = {
    {Course::BasicResource::MONEY, -5000},
    {Course::BasicResource::FOOD, -3000},
    {Course::BasicResource::WOOD, -3000},
    {Course::BasicResource::STONE, -2000},
    {Course::BasicResource::ORE, -1000}
};
const Course::ResourceMap VICTORYMONUMENT_PRODUCTION = {
    {Course::BasicResource::MONEY, 100},
};

// Building - Marketplace
const Course::ResourceMap MARKETPLACE_BUILD_COST = {
    {Course::BasicResource::MONEY, -100},
    {Course::BasicResource::FOOD, -200},
    {Course::BasicResource::WOOD, -150},
};
const Course::ResourceMap MARKETPLACE_PRODUCTION = {
    {Course::BasicResource::MONEY, 25},
};


// Building - Factory
const Course::ResourceMap FACTORY_BUILD_COST = {
    {Course::BasicResource::MONEY, -100},
    {Course::BasicResource::WOOD, -150},
    {Course::BasicResource::STONE, -100},

};
const Course::ResourceMap FACTORY_PRODUCTION = {
    {Course::BasicResource::MONEY, 50},
    {Course::BasicResource::WOOD, -25},
};



// Worker - Citizen
const Course::ResourceMapDouble CITIZEN_EFFICIENCY = {
    {Course::MONEY, 1.50},
    {Course::FOOD, 1.50},
    {Course::WOOD, 1.50},
    {Course::STONE, 1.25},
    {Course::ORE, 1.25}
};

const Course::ResourceMap CITIZEN_RECRUITMENT_COST = {
    {Course::MONEY, -50},
    {Course::FOOD, -50}
};

// Worker - EducatedCitizen
const Course::ResourceMapDouble EDUCATEDCITIZEN_EFFICIENCY = {
    {Course::MONEY, 3.00},
    {Course::FOOD, 3.00},
    {Course::WOOD, 3.00},
    {Course::STONE, 2.00},
    {Course::ORE, 2.00}
};

const Course::ResourceMap EDUCATEDCITIZEN_RECRUITMENT_COST = {
    {Course::MONEY, -300},
    {Course::FOOD, -150},
    {Course::ORE, -25}
};

const Course::ResourceMap BIRCH_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 1},
    {Course::WOOD, 2},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

const Course::ResourceMap EVERGREEN_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 1},
    {Course::WOOD, 2},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

const Course::ResourceMap GRASS_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 2},
    {Course::WOOD, 1},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

const Course::ResourceMap ANIMALS_BP = {
    {Course::MONEY, 5},
    {Course::FOOD, 5},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

const Course::ResourceMap STONE_BP = {
    {Course::MONEY, 1},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 3},
    {Course::ORE, 0},
};

const Course::ResourceMap SAND_BP = {
    {Course::MONEY, 3},
    {Course::FOOD, 2},
    {Course::WOOD, 0},
    {Course::STONE, 2},
    {Course::ORE, 0},
};

const Course::ResourceMap DIAMOND_BP = {
    {Course::MONEY, 30},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 3},
    {Course::ORE, 0},
};

const Course::ResourceMap ORE_BP = {
    {Course::MONEY, 0},
    {Course::FOOD, 0},
    {Course::WOOD, 0},
    {Course::STONE, 3},
    {Course::ORE, 1},
};

const Course::ResourceMap LAKE_BP = {
    {Course::MONEY, 3},
    {Course::FOOD, 3},
    {Course::WOOD, 0},
    {Course::STONE, 0},
    {Course::ORE, 0},
};

}

#endif // RESOURCES_H
