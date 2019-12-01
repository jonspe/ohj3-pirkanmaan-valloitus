#ifndef OBJECTMAPPINGS_H
#define OBJECTMAPPINGS_H

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "buildings/buildingbase.h"
#include "interfaces/igameeventhandler.h"
#include "interfaces/iobjectmanager.h"
#include "core/playerbase.h"

#include "Game/core/resources.h"

#include "Game/buildings/advancedfarm.h"
#include "Game/buildings/advancedlumbercamp.h"
#include "Game/buildings/advancedmine.h"
#include "Game/buildings/city.h"
#include "Game/buildings/colony.h"
#include "Game/buildings/diamondmine.h"
#include "Game/buildings/factory.h"
#include "Game/buildings/farm.h"
#include "Game/buildings/lumbercamp.h"
#include "Game/buildings/marketplace.h"
#include "Game/buildings/mine.h"
#include "Game/buildings/oremine.h"
#include "Game/buildings/university.h"
#include "Game/buildings/victorymonument.h"

const std::map<std::string, std::vector<std::string>> TILE_BUILDING_MAP =
{
    {"Grass", {
         "Colony",
         "Farm",
         "Advanced Farm",
         "Marketplace",
         "University",
         "Victory Monument",
         "Factory"
    }},

    {"Animals", {
         "Farm",
         "Advanced Farm"
    }},

    {"Evergreen", {
         "Colony",
         "Lumber Camp",
         "Advanced Lumber Camp"
    }},

    {"Birch", {
         "Colony",
         "Lumber Camp",
         "Advanced Lumber Camp"
    }},

    {"Stone", {
         "Mine",
         "Advanced Mine"
    }},

    {"Diamond", {
         "Diamond Mine"
    }},

    {"Ore", {
         "Ore Mine"
    }},

    {"Lake", {}}
};

const std::map<std::string, Course::ResourceMap> BUILD_COSTS =
{
    {"Colony",              ConstResources::COLONY_BUILD_COST},
    {"Farm",                ConstResources::FARM_BUILD_COST},
    {"Lumber Camp",         ConstResources::LUMBERCAMP_BUILD_COST},
    {"Marketplace",         ConstResources::MARKETPLACE_BUILD_COST},
    {"Mine",                ConstResources::MINE_BUILD_COST},
    {"University",          ConstResources::UNIVERSITY_BUILD_COST},
    {"Victory Monument",    ConstResources::VICTORYMONUMENT_BUILD_COST},
    {"Advanced Mine",       ConstResources::A_MINE_BUILD_COST},
    {"Advanced Farm",       ConstResources::A_FARM_BUILD_COST},
    {"Advanced Lumber Camp",ConstResources::A_LUMBERCAMP_BUILD_COST},
    {"Diamond Mine",        ConstResources::D_MINE_BUILD_COST},
    {"Ore Mine",            ConstResources::ORE_MINE_BUILD_COST},
    {"Factory",             ConstResources::FACTORY_BUILD_COST},
    {"Citizen",             ConstResources::CITIZEN_RECRUITMENT_COST},
    {"Educated Citizen",    ConstResources::EDUCATEDCITIZEN_RECRUITMENT_COST},
};

using BuildingConstructorPointer = std::function<std::shared_ptr<Course::BuildingBase>(
    std::shared_ptr<Course::iGameEventHandler>,
    std::shared_ptr<Course::iObjectManager>,
    std::shared_ptr<Course::PlayerBase>)>;

namespace  {
    template<typename T>
    BuildingConstructorPointer makeConstructor()
    {
        BuildingConstructorPointer ctor = std::make_shared<T,
                std::shared_ptr<Course::iGameEventHandler>,
                std::shared_ptr<Course::iObjectManager>,
                std::shared_ptr<Course::PlayerBase>>;
        return ctor;
    }
}

const std::map<std::string, BuildingConstructorPointer> BUILDING_CTOR_MAP =
{
    {"Advanced Farm",       makeConstructor<AdvancedFarm>()},
    {"Advanced Lumber Camp",makeConstructor<AdvancedLumberCamp>()},
    {"Advanced Mine",       makeConstructor<AdvancedMine>()},
    {"City",                makeConstructor<City>()},
    {"Colony",              makeConstructor<Colony>()},
    {"Diamond Mine",        makeConstructor<DiamondMine>()},
    {"Factory",             makeConstructor<Factory>()},
    {"Farm",                makeConstructor<Farm>()},
    {"Lumber Camp",         makeConstructor<LumberCamp>()},
    {"Marketplace",         makeConstructor<Marketplace>()},
    {"Mine",                makeConstructor<Mine>()},
    {"Ore Mine",            makeConstructor<OreMine>()},
    {"University",          makeConstructor<University>()},
    {"Victory Monument",    makeConstructor<VictoryMonument>()},

};


#endif // OBJECTMAPPINGS_H
