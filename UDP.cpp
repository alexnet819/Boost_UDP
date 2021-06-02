#include "UDP.h"

#include<boost/asio.hpp>
using boost::asio::ip::udp;

//Client

UDP_Client::~UDP_Client() {
	socket_.close();
}


bool UDP_Client::set_Broadcast(bool flag)
{
	try {
		boost::asio::socket_base::broadcast option(flag);
		socket_.set_option(option);
		return true;
	}
	catch (std::exception &e) {
		return false;
	}
}

bool UDP_Client::send(const boost::array<char, 8192> msg)
{
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool UDP_Client::send(const std::string msg)
{
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_ ) > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool UDP_Client::send(const std::string ip,const int port, const std::string msg)
{
	//boost::asio::ip::udp::endpoint(udp::v4(), stoi(port));
	boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ip), port);
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), destination) > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool UDP_Client::send(const std::string ip, const int port, const boost::array<char, 8192> msg)
{
	boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ip), port);
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		return true;
	}
	else {
		return false;
	}

}


//Server


UDP_Server::~UDP_Server() 
{
	this->socket_.close();
}


void UDP_Server::Start_Receive(bool mode)
{
	if (mode) {
		while (1) {
			udp::endpoint endpoint;
			//socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&UDP_Server::handle_receive, this,boost::asio::placeholders::error));
			size_t len = socket_.receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_);
			std::cout << "receive_from==" << remote_endpoint_.address().to_string() << std::endl;

			std::cout << "recive string=";
			std::cout.write(recv_buffer_.data(), len);
			std::cout << std::endl;
			if (END_FLAG) return;
		}
	}
	else {
		udp::endpoint endpoint;
		//socket_.async_receive_from(boost::asio::buffer(recv_buffer_), remote_endpoint_,boost::bind(&UDP_Server::handle_receive, this,boost::asio::placeholders::error));
		size_t len = socket_.receive_from(boost::asio::buffer(recv_buffer_), endpoint);
		std::cout << "receive_from==" << endpoint.address().to_string() << std::endl;

		std::cout.write(recv_buffer_.data(), len);

	}


}

bool UDP_Server::set_Broadcast(bool flag)
{
	try {
		boost::asio::socket_base::broadcast option(flag);
		socket_.set_option(option);
		return true;
	}
	catch (std::exception &e) {
		return false;
	}
}

bool UDP_Server::send(const boost::array<char, 8192> msg)
{
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool UDP_Server::send(const std::string msg)
{
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool UDP_Server::send(const std::string ip, const int port, const std::string msg)
{
	//boost::asio::ip::udp::endpoint(udp::v4(), stoi(port));
	boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ip), port);
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), destination) > 0) {
		return true;
	}
	else {
		return false;
	}

}

bool UDP_Server::send(const std::string ip, const int port, const boost::array<char, 8192> msg)
{
	boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ip), port);
	if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		return true;
	}
	else {
		return false;
	}

}

void UDP_Server::send(const std::string ip, const int port)
{
	while (1) {
		boost::asio::ip::udp::endpoint destination(boost::asio::ip::address::from_string(ip), port);
		std::string msg;
		std::cout << "send message=";
		std::cin >> msg;
		if (socket_.send_to(boost::asio::buffer(msg, msg.size()), endpoint_) > 0) {
		}
		else {
		}
	}

}


//void UDP_Server::handle_receive(const boost::system::error_code& error)
//{
//	if (!error)
//	{
//		boost::shared_ptr<std::string> message(new std::string(make_daytime_string()));
//
//		socket_.async_send_to(boost::asio::buffer(*message), remote_endpoint_,boost::bind(&UDP_Server::handle_send, this, message));
//
//		start_receive();
//	}
//}
