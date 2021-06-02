#include"UDP.h"
#include<boost/asio.hpp>
#include<thread>

#include <iostream>
int main(int argc, char * argv[]) {


	try
	{
		boost::asio::io_context io_context, io_context2;
		UDP_Server server(io_context, 1000);
		//�T�[�o�̃X���b�h�𗧂Ă܂�
		std::thread sv(&UDP_Server::Start_Receive, &server, true);
		sv.detach();
		//Server��Send�@�\���������Ă��܂�
		while (1) {
			std::string str;
			std::cout << "input string:";
			std::cin >> str;
			//����(ip(str),port,���M������������)
			server.send("192.168.116.65", 1000, str);
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}


	return 0;

}

