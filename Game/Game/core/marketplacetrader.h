#ifndef MARKETPLACETRADER_H
#define MARKETPLACETRADER_H
#include <string>

class MarketplaceTrader
{
public:
    MarketplaceTrader();

    int getFoodBuyPrice();

    int getWoodBuyPrice();

    int getStoneBuyPrice();

    int getOreBuyPrice();

    int getFoodSellPrice();

    int getWoodSellPrice();

    int getStoneSellPrice();

    int getOreSellPrice();

    void changeFoodMultiplier(std::string sign);

    void changeWoodMultiplier(std::string sign);

    void changeStoneMultiplier(std::string sign);

    void changeOreMultiplier(std::string sign);

private:
    double food_price_multiplier = 1.00;
    double wood_price_multiplier = 1.00;
    double stone_price_multiplier = 1.00;
    double ore_price_multiplier = 1.00;

};

#endif // MARKETPLACETRADER_H
