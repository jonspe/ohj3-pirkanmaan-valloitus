#include "Game/core/marketplacetrader.h"

MarketplaceTrader::MarketplaceTrader()
{
    m_multiplier_map[Course::BasicResource::FOOD] = 1.00;
    m_multiplier_map[Course::BasicResource::WOOD] = 1.00;
    m_multiplier_map[Course::BasicResource::STONE] = 1.00;
    m_multiplier_map[Course::BasicResource::ORE] = 1.00;

    m_sell_price_map[Course::BasicResource::FOOD] = 80;
    m_sell_price_map[Course::BasicResource::WOOD] = 125;
    m_sell_price_map[Course::BasicResource::STONE] = 200;
    m_sell_price_map[Course::BasicResource::ORE] = 500;

    m_buy_price_map[Course::BasicResource::FOOD] = -100;
    m_buy_price_map[Course::BasicResource::WOOD] = -150;
    m_buy_price_map[Course::BasicResource::STONE] = -250;
    m_buy_price_map[Course::BasicResource::ORE] = -1000;
}


int MarketplaceTrader::getBuyPrice(Course::BasicResource resource) const
{
     return int(m_buy_price_map.at(resource) * m_multiplier_map.at(resource));
}

int MarketplaceTrader::getSellPrice(Course::BasicResource resource) const
{
     return int(m_sell_price_map.at(resource) * m_multiplier_map.at(resource));
}

void MarketplaceTrader::changeMultiplier(Course::BasicResource resource, std::string sign)
{
    if (sign == "+")
    {
        m_multiplier_map[resource] += 0.01;
    }else if (sign == "-"){
        m_multiplier_map[resource] -= 0.01;
    }

    if (m_multiplier_map[resource] < 0.10){
        m_multiplier_map[resource] = 0.10;
    }
}



