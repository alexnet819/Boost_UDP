#include"UDP.h"
#include<boost/asio.hpp>
#include<thread>

#include <iostream>
int main(int argc, char * argv[]) {


	try
	{
		boost::asio::io_context io_context, io_context2;
		UDP_Server server(io_context, 1000);
		//サーバのスレッドを立てます
		std::thread sv(&UDP_Server::Start_Receive, &server, true);
		sv.detach();
		//ServerにSend機能を実装しています
		while (1) {
			std::string str;
			std::cout << "input string:";
			std::cin >> str;
			//引数(ip(str),port,送信したい文字列)
			server.send("192.168.116.65", 1000, str);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;

}

