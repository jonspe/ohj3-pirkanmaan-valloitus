#ifndef MARKETPLACETRADER_H
#define MARKETPLACETRADER_H
#include <string>
#include "core/basicresources.h"
#include <map>

class MarketplaceTrader
{
public:
    MarketplaceTrader();
    /**
     * @brief returns buy price of given resource
     * @param resource type of resource of which the price is being requested :--)
     */
    int getBuyPrice(Course::BasicResource resource);
    /**
     * @brief returns sell price of given resource
     * @param resource type of resource of which the price is being requested :--)
     */
    int getSellPrice(Course::BasicResource resource);

    /**
     * @brief changes resource price multiplier on buy/sell event
     * @param resource type of resource of which the price is being requested :--)
     * @param sign + or - depending on value change
     */

    void changeMultiplier(Course::BasicResource resource, std::string sign);

private:

    std::map<Course::BasicResource, double> multiplier_map;

    std::map<Course::BasicResource, int> sell_price_map;

    std::map<Course::BasicResource, int> buy_price_map;


};

#endif // MARKETPLACETRADER_H
