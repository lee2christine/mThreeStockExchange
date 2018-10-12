#ifndef Order_h_
#define Order_h_


// WHAT'S WRONG HERE???
#include <thread>
#include <deque>
#include <string>
#include <mutex>

class Order {
    friend std::istream& operator>>( std::istream&, Order& );
public:
    enum Direction { Buy = '1', Sell = '2' };
private:
    std::string symbol_;
    Direction direction_;
    size_t quantity_;
    double limitPrice_;
    //int orderId_;
public:

    Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice );
    //Order( int orderID, const std::string& symbol, Direction direction,
    //size_t quantity, double limitPrice );

    char getDirection() const { if ( direction_ == '1') return '1'; else return '2'; }

    std::string serialise() const;
    Order() = default;
    std::string toString() const;
    void FIX(int orderId);

    const std::string& symbol() const;
    double price() const;
    size_t quantity() const;
    char direction() const;

    bool operator==(const Order& rhs) const;
};

std::istream& operator>>( std::istream&, Order& );

inline
const std::string& Order::symbol() const {
	return symbol_;
}	

inline 
double Order::price() const {
	return limitPrice_;
}

inline
size_t Order::quantity() const {
        return quantity_;
}

inline
char Order::direction() const {
        return getDirection();
}


inline 
bool Order::operator==(const Order& rhs) const {
	return ((symbol_ == rhs.symbol_) 
		&& (direction_ == rhs.direction_)
		&& (quantity_ == rhs.quantity_)
		&& (limitPrice_ == rhs.limitPrice_)
		);
}

#endif // Order_h_
