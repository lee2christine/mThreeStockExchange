#include "order.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

std::istream& operator>>( std::istream& is, Order::Direction& direction ){
	std::string d;

	is >> d;
	if ( d == "1" ) {
		direction = Order::Direction::Buy;
	} else if ( d == "2" ) {
		direction = Order::Direction::Sell;
	} else {
		throw std::runtime_error("Can't read a direction: it must be 1 or 2");
	}

	return is;
}
std::istream& operator>>( std::istream& is, Order& order ){
	std::string symbol;
	Order::Direction direction;
	size_t quantity;
	double limitPrice;

	is >> symbol;
	if ( is.eof() ) return is;
	is >> direction;
	is >> quantity;
	is >> limitPrice;

	order = Order(symbol, direction, quantity, limitPrice);
	return is;
}

Order::Order( const std::string& symbol, Direction direction,
		size_t quantity, double limitPrice ) :
		symbol_( symbol ),
		direction_( direction ),
		quantity_( quantity ),
		limitPrice_( limitPrice ){
}

std::string Order::serialise() const {
	std::ostringstream oss;
	oss << symbol_ << " " << static_cast<char>(direction_) << " " << quantity_ << " " << limitPrice_;
	return oss.str();
}

std::string Order::toString() const {
	std::ostringstream oss;
	oss << "{ Order symbol '" << symbol_
		<< "' direction '" << static_cast<char>(direction_)
		<< "' quantity '" << quantity_
		<< "' limit price '" << limitPrice_
		<< "' }";
	return oss.str();
}


void Order::FIX(int instIndex) {
	int orderId = 0;
	std::string FIX = "37=" + std::to_string(++orderId)
				+ " | 44=" + std::to_string(limitPrice_) 
				+ " | 53=" + std::to_string(quantity_) 
				+ " | 54=" + static_cast<char>(direction_)
				+ " | 55=" + symbol_
				+ '\n';  	

	std::cout << "8=FIX.4.2 | 9=" << FIX.length() << " | " << FIX;
}




