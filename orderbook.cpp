#include "orderbook.h"
#include <utility>
#include <unordered_map>

void OrderBook::addOrder(const std::string& client, const Order& order){
        ClientOrderPair newPair(client, order);
	std::string symbol = order.symbol();
	if(order.getDirection() == '1'){
		auto it = buyOrders_.find(symbol);
  		if(it != buyOrders_.end()){
			(it->second).push_back(newPair);
		}
		else{
        	std::vector< ClientOrderPair > orders = {newPair};
			buyOrders_[symbol] = orders;
		}  
	}

	else if (order.getDirection() == '2'){
		auto it = sellOrders_.find(symbol);
		if(it != sellOrders_.end()){
			(it->second).push_back(newPair);
		}
		else{
			std::vector< ClientOrderPair > orders = {newPair};
			sellOrders_[symbol] = orders;
		}
	}
}

Matches OrderBook::findAndExecuteMatches(){	
	Matches matches;
	if (buyOrders_.size() == 0 || sellOrders_.size() == 0){
		return matches;
	}
	auto it = buyOrders_.begin();
	while (it != buyOrders_.end()){
		std::string key = it->first;
		if ((buyOrders_.find(key) != buyOrders_.end()) && (sellOrders_.find(key) != sellOrders_.end())){
			for(unsigned int i = 0; i != sellOrders_[key].size(); ++i){
				for(unsigned int j = 0; j != sellOrders_[key].size(); ++j){
					if (buyOrders_[key][i].second.price() == sellOrders_[key][j].second.price()){
						ClientOrderPair buyPair(buyOrders_[key][i].first, buyOrders_[key][i].second);
						ClientOrderPair sellPair(sellOrders_[key][j].first, sellOrders_[key][j].second);
						std::pair<ClientOrderPair, ClientOrderPair> match(buyPair, sellPair);
						matches.push_back(match);
					}
				}
			}
		}
		it++;
	}
	return matches;
}
