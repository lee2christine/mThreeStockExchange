#include <iostream>
#include <time.h>
#include <unistd.h>
#include <chrono>
#include <stdlib.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <order.h>
#include <cstdlib>
using boost::asio::ip::tcp;

int orderId=0;
std::string instruments[]{"VOD.L","HSBA.L"};
size_t sizes[2];
double benchmarkPrices[2];

void sendNewOrder(int orderId, tcp::socket& socket ) {
	for(int i = 0; i < 2; i ++){
		sizes[i] = rand() % 10000 + 1;
		sleep(3);
		benchmarkPrices[i] = ((double)rand() % 10000) / RAND_MAX + 1.0;
		sleep(2);		
	}
	boost::system::error_code ignored_error;
	int instIndex=orderId%2;
	Order newOrder( { instruments[instIndex], Order::Buy, sizes[instIndex], benchmarkPrices[instIndex]} ); //TODO make the numbers random
	std::cout<<"Sending order "<<orderId++<<" "<<newOrder.toString()<<"\n";
	//TASK change the protocol to FIX
	boost::asio::write(socket, boost::asio::buffer("NEW_ORDER" + newOrder.serialise()), ignored_error);
}

int main(int argc, char* argv[]){
	srand(time(NULL));
	try{
		if (argc != 4){
			std::cerr << "Usage: client <host> <port> <clientid>\n";
			return 1;
		}

		boost::asio::io_service io_service;

		tcp::resolver resolver(io_service);
		std::string port( argv[2] );
		tcp::resolver::query query(argv[1], port );
		std::string clientid(argv[3]);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		std::cout<<"Connecting to server: "<<argv[1]<<":"<<port<<"\n";
		boost::asio::connect(socket, endpoint_iterator);

		{
			std::string message = "HELLO_I_AM " + clientid;
			boost::system::error_code ignored_error; //TASK don't ignore errors
			std::cout<<"Logging in\n";
			boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}
		std::cout<<"sleep 5\n";
		sleep(5);
		int numOrders=10+rand()%100;
		for (int i = 0; i < numOrders; ++i) { //TASK have the server respond to the client with fill messages
			srand(time(NULL));
			unsigned int seconds_ = rand() % 4;	
			sendNewOrder( socket );
			if( seconds_ == 0) usleep(100000);
			else sleep(seconds_);
		}
		std::cout<<"Logging out\n";
		{
		std::string message = "QUIT ";
			boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		}

//		for (;;)
//		{
//			boost::array<char, 128> buf;
//			boost::system::error_code error;
//
//			size_t len = socket.read_some(boost::asio::buffer(buf), error);
//
//			if (error == boost::asio::error::eof)
//				break; // Connection closed cleanly by peer.
//			else if (error)
//				throw boost::system::system_error(error); // Some other error.
//
//			std::cout.write(buf.data(), len);
//		}
	}catch (std::exception& e){
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
