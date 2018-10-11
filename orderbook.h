#ifndef OrderBook_h_
#define OrderBook_h_
#include <map>
#include <vector>
#include <thread>
#include <deque>
#include <string>
#include <mutex>
#include "order.h"

class WhatTypeShouldThisBe {
};
class Matches {
};

class OrderBook {
private:
    std::map<std::string, std::vector<Order>> buyOrders_;
    std::map<std::string, std::vector<Order>> sellOrders_;
public:
    char addOrder(const std::string& client, const Order& order);

    /**
     * Look for matches, execute the matches, and return the fills
     */
    Matches findAndExecuteMatches();
};

std::istream& operator>>( std::istream&, Order& );

#endif // OrderBook_h_

