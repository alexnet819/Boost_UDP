#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)
#ifndef __UDP_H__
#define __UDP_H__



#include<vector>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

using boost::asio::ip::udp;

class UDP_Client
{
public:
	UDP_Client(boost::asio::io_service& io_service, const std::string& host, const int& port) : io_service_(io_service), socket_(io_service, udp::endpoint(udp::v4(), port)) 
	{
		udp::resolver resolver(io_service_);
		udp::resolver::query query(udp::v4(), host, std::to_string(port));
		udp::resolver::iterator iter = resolver.resolve(query);
		endpoint_ = *iter;

		recvBuffer_.fill(0);
		//deadline_.expires_at(boost::posix_time::pos_infin);
	};


	//UDPClient() : io_service_(io_service_), socket_(io_service_, udp::endpoint(udp::v4(), 0));
	~UDP_Client();
	//broadcast�������ꍇ�͂��̊֐����Ăяo���Ă�������
	bool set_Broadcast(bool flag);
	bool send(const boost::array<char, 8192>);
	bool send(const std::string msg);
	bool send(const std::string ip, const int port, const std::string msg);
	bool send(const std::string ip, const int port, const boost::array<char, 8192> msg);
private:
	std::array<char, 8192> recvBuffer_;
	boost::asio::io_service& io_service_;
	//udp_socket
	udp::socket socket_;
	udp::endpoint endpoint_;

	std::string data_;
	//deadline_timer deadline_;

	//static void handle_receive(const boost::system::error_code& ec, std::size_t length,
	//	boost::system::error_code* out_ec, std::size_t* out_length) {
	//	*out_ec = ec;
	//	*out_length = length;
	//}
};

class UDP_Server 
{
public:
	UDP_Server(boost::asio::io_context& io_context, const int port) : io_context_(io_context), socket_(io_context, udp::endpoint(udp::v4(), port))
	{
		udp::resolver resolver(io_context_);
		udp::resolver::query query(udp::v4(), "0.0.0.0", std::to_string(port));
		udp::resolver::iterator iter = resolver.resolve(query);
		endpoint_ = *iter;

		recvBuffer_.fill(0);
	};

	//UDP_Server();
	~UDP_Server();
	//UDP��Receive�֐��ł��@�����@false=��񂾂��̎�M true=������̎�M
	void Start_Receive(bool mode);

	//Start_Receive��true�̏ꍇ�̊֐��I���t���O
	bool END_FLAG = false;
	//broadcast�������ꍇ�͂��̊֐����Ăяo���Ă�������
	bool set_Broadcast(bool flag);
	bool send(const boost::array<char, 8192>);
	bool send(const std::string msg);
	bool send(const std::string ip, const int port, const std::string msg);
	bool send(const std::string ip, const int port, const boost::array<char, 8192> msg);
    void send(const std::string ip, const int port);

private:

	boost::asio::io_service& io_context_;
	std::array<char, 8192> recvBuffer_;
	//UDPsocket
	udp::socket socket_;
	udp::endpoint endpoint_;
	udp::endpoint remote_endpoint_;
	boost::array<char, 8192> recv_buffer_;
};

#endif // !__UDP_H__