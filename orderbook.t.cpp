#include <gtest/gtest.h>
#include <stdexcept>
#include "orderbook.h"
#include "order.h"

TEST (OrderBookTest, test1)
{
	OrderBook book;
	Order buy("GOOGL:US", Order::Buy, 100, 1200.00);
	book.addOrder("matt", buy);
	EXPECT_EQ(1,1);
}

TEST (OrderBookTest, test2)
{
}

TEST (OrderBookTest, test3)
{
}


