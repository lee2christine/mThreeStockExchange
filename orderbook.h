#ifndef OrderBook_h_
#define OrderBook_h_
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <deque>
#include <mutex>
#include "order.h"

class Matches {
};

class OrderBook {
private:
    std::unordered_map< std::string, std::vector<std::pair< std::string, Order> > > buyOrders_;
    std::unordered_map< std::string, std::vector<std::pair< std::string, Order> > > sellOrders_;
public:
    void addOrder(const std::string& client, const Order& order);

    /**
     * Look for matches, execute the matches, and return the fills
     */
    Matches findAndExecuteMatches();
};

std::istream& operator>>( std::istream&, Order& );

#endif // OrderBook_h_

