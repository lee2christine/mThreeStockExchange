#include "orderbook.h"
char OrderBook::addOrder(const std::string& client, const Order& order){
        std::vector<Order> insOrder;
        insOrder.push_back(order);

        if(order.getDirection() == '1'){
		auto insTest = buyOrders_.find(client);
  		if(insTest != buyOrders_.end()){
			insOrder = insTest->second;
			insOrder.push_back(order);
			insTest->second = insOrder;
			return 'B';
		}
		else{
			buyOrders_.emplace(client, insOrder);
			return 'b';
		}  
        }

        else if (order.getDirection() == '2'){
		auto insTest = sellOrders_.find(client);
                if(insTest != sellOrders_.end()){
                        insOrder = insTest->second;
                        insOrder.push_back(order);
                        insTest->second = insOrder;
                        return 'S';
                }
                else{
                        sellOrders_.emplace(client, insOrder);
                        return 's';
                }

	}

        else return 'X';

}

