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
public:
    getDirection() { if ( direction_ == '1') return true; else return false;
    Order( const std::string& symbol, Direction direction,
    size_t quantity, double limitPrice );
    std::string serialise() const;
    Order() = default;
    std::string toString() const;
};

std::istream& operator>>( std::istream&, Order& );

#endif // Order_h_
