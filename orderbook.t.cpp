#include <gtest/gtest.h>
#include <stdexcept>
#include <sstream>
#include "orderbook.h"
#include "order.h"

TEST (OrderBookTest, test1)
{
	EXPECT_EQ(1,1);
	OrderBook book;
	Order buy("GOOGL:US", Order::Buy, 100, 1200.00);
	Order sell("GOOGL:US", Order::Sell, 100, 1200.00);
	book.addOrder("matt", buy);
	book.addOrder("christine", sell);
	
	std::stringstream ss;
	book.print(ss);
	EXPECT_EQ("Buy Orders: GOOGL:US matt 1 100 1200 -- Sell Orders: GOOGL:US christine 2 100 1200", ss.str());

	Matches actual = book.findAndExecuteMatches();	
	
	ClientOrderPair pair1("matt", buy);
	ClientOrderPair pair2("christine", sell);
	std::pair<ClientOrderPair, ClientOrderPair> match(pair1, pair2);
	
	Matches expected = {match};
	EXPECT_EQ(expected.size(), actual.size());
	for(unsigned int i = 0; i < actual.size(); ++i){
		EXPECT_TRUE(expected[i].first.first == actual[i].first.first);
		EXPECT_TRUE(expected[i].first.second == actual[i].first.second);
		EXPECT_TRUE(expected[i].first.second == actual[i].first.second);
		EXPECT_TRUE(expected[i].second.second == actual[i].second.second);
	}
}

TEST (OrderBookTest, test2)
{
}

TEST (OrderBookTest, test3)
{
}


