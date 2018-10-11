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
<<<<<<< HEAD
    char getDirection() const { if ( direction_ == '1') return true; else return false; }
    Order( const std::string& symbol, Direction direction, size_t quantity, double limitPrice );
    //Order( int orderID, const std::string& symbol, Direction direction,
    //size_t quantity, double limitPrice );
=======
    char getDirection() const { if ( direction_ == '1') return '1'; else return '2'; }
    Order( const std::string& symbol, Direction direction,
    size_t quantity, double limitPrice );
>>>>>>> 968ab1c74384946accbcaefa30dee2ebf9e8e92b
    std::string serialise() const;
    Order() = default;
    std::string toString() const;
    void FIX(int orderId);

};

std::istream& operator>>( std::istream&, Order& );

#endif // Order_h_
