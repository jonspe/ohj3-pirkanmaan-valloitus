#include "marketplacetrader.h"

MarketplaceTrader::MarketplaceTrader()
{

}


int MarketplaceTrader::getFoodBuyPrice()
{
    return int((-100 * food_price_multiplier));
}

int MarketplaceTrader::getWoodBuyPrice()
{
    return int((-150 * wood_price_multiplier));
}

int MarketplaceTrader::getStoneBuyPrice()
{
    return int((-300 * stone_price_multiplier));
}

int MarketplaceTrader::getOreBuyPrice()
{
    return int((-1000 * ore_price_multiplier));
}

int MarketplaceTrader::getFoodSellPrice()
{
    return int((50 * food_price_multiplier));
}

int MarketplaceTrader::getWoodSellPrice()
{
    return int((75 * wood_price_multiplier));
}

int MarketplaceTrader::getStoneSellPrice()
{
    return int((150 * stone_price_multiplier));
}

int MarketplaceTrader::getOreSellPrice()
{
    return int((500 * ore_price_multiplier));
}

void MarketplaceTrader::changeFoodMultiplier(std::string sign)
{
    if (sign == "+")
    {
        food_price_multiplier += 0.01;
    }else if (sign == "-"){
        food_price_multiplier -= 0.01;
    }

    if (food_price_multiplier < 0.10){
        food_price_multiplier = 0.10;
    }
}

void MarketplaceTrader::changeWoodMultiplier(std::string sign)
{
    if (sign == "+")
    {
        wood_price_multiplier += 0.01;
    }else if (sign == "-"){
        wood_price_multiplier -= 0.01;
    }

    if (food_price_multiplier < 0.10){
        wood_price_multiplier = 0.10;
    }
}

void MarketplaceTrader::changeStoneMultiplier(std::string sign)
{
    if (sign == "+")
    {
        stone_price_multiplier += 0.01;
    }else if (sign == "-"){
        stone_price_multiplier -= 0.01;
    }

    if (stone_price_multiplier < 0.10){
        stone_price_multiplier = 0.10;
    }
}

void MarketplaceTrader::changeOreMultiplier(std::string sign)
{
    if (sign == "+")
    {
        ore_price_multiplier += 0.01;
    }else if (sign == "-"){
        ore_price_multiplier -= 0.01;
    }

    if (ore_price_multiplier < 0.10){
        ore_price_multiplier = 0.10;
    }
}
