#include <gtest/gtest.h>
#include <stdexcept>
#include <sstream>
#include "orderbook.h"
#include "order.h"

TEST (OrderBookTest, Add)
{
	OrderBook book;
	Order buy("GOOGL:US", Order::Buy, 100, 1200.00);
	Order sell("AMZN:US", Order::Sell, 300, 1700.00);
	book.addOrder("matt", buy);
	book.addOrder("christine", sell);
	
	std::stringstream ss;
	book.print(ss);
	EXPECT_EQ("Buy Orders: GOOGL:US matt 1 100 1200 -- Sell Orders: AMZN:US christine 2 300 1700", ss.str());
}

TEST (OrderBookTest, Match)
{
	OrderBook book;
	Order buy1("GOOGL:US", Order::Buy, 100, 1200.00);
	Order sell1("GOOGL:US", Order::Sell, 100, 1200.00);
	book.addOrder("matt", buy1);
	book.addOrder("christine", sell1);
	
	Matches actual1 = book.findAndExecuteMatches();	
	
	ClientOrderPair pair1a("matt", buy1);
	ClientOrderPair pair1b("christine", sell1);
	std::pair<ClientOrderPair, ClientOrderPair> match1(pair1a, pair1b);
	
	Matches expected = {match1};
	EXPECT_EQ(expected.size(), actual1.size());
	for(unsigned int i = 0; i < actual1.size(); ++i){
		EXPECT_TRUE(expected[i].first.first == actual1[i].first.first);
		EXPECT_TRUE(expected[i].first.second == actual1[i].first.second);
		EXPECT_TRUE(expected[i].first.second == actual1[i].first.second);
		EXPECT_TRUE(expected[i].second.second == actual1[i].second.second);
	}
	
	Order buy2("AMZN:US", Order::Buy, 50, 1700.00);
	Order sell2("AMZN:US", Order::Sell, 50, 1700.00);
	book.addOrder("andrew", buy2);
	book.addOrder("christine", sell2);
	
	ClientOrderPair pair2a("andrew", buy2);
	ClientOrderPair pair2b("christine", sell2);
	std::pair<ClientOrderPair, ClientOrderPair> match2(pair2a, pair2b);
	
	Matches actual2 = book.findAndExecuteMatches();
	
	expected.push_back(match2);
	EXPECT_EQ(expected.size(), actual2.size());
	for(unsigned int i = 0; i < actual2.size(); ++i){

		// TODO: Find Function because unordered maps are in no particular order
		EXPECT_TRUE(expected[i].first.first == actual2[i].first.first);
		EXPECT_TRUE(expected[i].first.second == actual2[i].first.second);
		EXPECT_TRUE(expected[i].first.second == actual2[i].first.second);
		EXPECT_TRUE(expected[i].second.second == actual2[i].second.second);
	}
}

TEST (OrderBookTest, test3)
{
}


