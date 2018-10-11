#include "orderbook.h"
#include <utility>
#include <unordered_map>

void OrderBook::addOrder(const std::string& client, const Order& order){
        std::pair<std::string, Order> clientOrderPair(client, order);
	std::string symbol = order.symbol();

	if(order.getDirection() == '1'){
		auto it = buyOrders_.find(symbol);
  		if(it != buyOrders_.end()){
			(it->second).push_back(clientOrderPair);

			/*insOrder = insTest->second;
			insOrder.push_back(order);
			insTest->second = insOrder;*/
		}
		else{
        		std::vector< std::pair<std::string, Order> > orders = {clientOrderPair};
        		//orders.push_back(order);
			buyOrders_[symbol] = orders;
		}  
        }

        else if (order.getDirection() == '2'){
		auto it = sellOrders_.find(symbol);
                if(it != sellOrders_.end()){
			(it->second).push_back(clientOrderPair);
                        /*insOrder = insTest->second;
                        insOrder.push_back(order);
                        insTest->second = insOrder;*/
                }
                else{
        		std::vector< std::pair<std::string, Order> > orders = {clientOrderPair};
			sellOrders_[symbol] = orders;
        		//orders.push_back(order);
        		//std::vector<Order> orders = {order};
			//sellOrders_.emplace(client, orders);
		}

	}
}
/*
const std::vector<std::pair<Order,Order>>& OrderBook::findAndExecuteMatches(){	
	std::vector<std::pair<Order, Order>> Matches;
	auto it = buyOrders_.begin();
	while (it != buyOrders_.end()){
		
	}
}*/
