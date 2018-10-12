#ifndef OrderBook_h_
#define OrderBook_h_
#include <string>
#include <vector>
#include <unordered_map>
#include <thread>
#include <deque>
#include <mutex>
#include "order.h"
#include <iostream>

typedef std::pair<std::string, Order> ClientOrderPair;
typedef std::vector<std::pair<ClientOrderPair, ClientOrderPair>> Matches;
typedef std::unordered_map<std::string, std::vector<ClientOrderPair>> OrderMap;

class OrderBook {
private:
     OrderMap buyOrders_;
     OrderMap sellOrders_;
public:
    void addOrder(const std::string& client, const Order& order);
    void print(std::ostream& out) const;
    std::vector<ClientOrderPair> buy() const;
    /**
     * Look for matches, execute the matches, and return the fills
     */
    Matches findAndExecuteMatches();
};

std::istream& operator>>( std::istream&, Order& );
/*
inline
std::vector<ClientOrderPair> OrderBook::buy() const{
     return buyOrders_->second;
}*/

inline 
void OrderBook::print(std::ostream& out) const {
    out << "Buy Orders: ";
    if (buyOrders_.size() != 0){
	auto it = buyOrders_.begin();
    	while (it != buyOrders_.end()){
	    out << it->first;
            for(unsigned int i = 0; i != it->second.size(); ++i){
		out << " " << (it->second)[i].first
			<< " " << (it->second)[i].second.direction()
			<<  " " << (it->second)[i].second.quantity()
			<<  " " << (it->second)[i].second.price();
            }
            ++it;
            if (it != buyOrders_.end()){
                out << ", ";
            }
	}	
    }

    out << " -- Sell Orders: ";
    if (sellOrders_.size() != 0){
        auto it = sellOrders_.begin();
        while (it != sellOrders_.end()){
            out << it->first;
            for(unsigned int i = 0; i != it->second.size(); ++i){
                out << " " << (it->second)[i].first
                        << " " << (it->second)[i].second.direction()
                        <<  " " << (it->second)[i].second.quantity()
                        <<  " " << (it->second)[i].second.price();
            }
            ++it;
            if (it != sellOrders_.end()){
                out << ", ";
            }
        }
    }
}

#endif // OrderBook_h_

