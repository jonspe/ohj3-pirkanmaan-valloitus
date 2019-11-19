#include "Game/core/marketplacetrader.h"

MarketplaceTrader::MarketplaceTrader()
{
    multiplier_map[Course::BasicResource::FOOD] = 1.00;
    multiplier_map[Course::BasicResource::WOOD] = 1.00;
    multiplier_map[Course::BasicResource::STONE] = 1.00;
    multiplier_map[Course::BasicResource::ORE] = 1.00;

    sell_price_map[Course::BasicResource::FOOD] = 50;
    sell_price_map[Course::BasicResource::WOOD] = 75;
    sell_price_map[Course::BasicResource::STONE] = 150;
    sell_price_map[Course::BasicResource::ORE] = 500;

    buy_price_map[Course::BasicResource::FOOD] = -100;
    buy_price_map[Course::BasicResource::WOOD] = -150;
    buy_price_map[Course::BasicResource::STONE] = -300;
    buy_price_map[Course::BasicResource::ORE] = -1000;
}


int MarketplaceTrader::getBuyPrice(Course::BasicResource resource)
{
     return int(buy_price_map[resource] * multiplier_map[resource]);
}

int MarketplaceTrader::getSellPrice(Course::BasicResource resource)
{
     return int(sell_price_map[resource] * multiplier_map[resource]);
}

void MarketplaceTrader::changeMultiplier(Course::BasicResource resource, std::string sign)
{
    if (sign == "+")
    {
        multiplier_map[resource] += 0.01;
    }else if (sign == "-"){
        multiplier_map[resource] -= 0.01;
    }

    if (multiplier_map[resource] < 0.10){
        multiplier_map[resource] = 0.10;
    }


}



