
#include "./WebServer.h"

#include <stdio.h>
#include <string> 
#include <boost/format.hpp>
#include <boost/asio.hpp> 

using boost::wformat;

namespace web_server_example
{
	boost::asio::io_service g_io_service;
	boost::asio::ip::tcp::endpoint g_endpoint(boost::asio::ip::tcp::v4(), 7777);
	boost::asio::ip::tcp::acceptor g_acceptor(g_io_service, g_endpoint);
	boost::asio::ip::tcp::socket g_socket(g_io_service);
	std::string g_data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
}

using web_server_example::g_io_service;
using web_server_example::g_endpoint;
using web_server_example::g_acceptor;
using web_server_example::g_socket;
using web_server_example::g_data;

void WriteHandler(const boost::system::error_code& error_code, std::size_t bytes_transferred)
{
	if (error_code)
	{
		wprintf((wformat(L"WriteHandler - Error: %s\n") % error_code).str().c_str());
		return;
	}

	wprintf((wformat(L"WriteHandler - Transfered %d bytes\n") % bytes_transferred).str().c_str());
}

void AcceptHandler(const boost::system::error_code& error_code)
{
	if (error_code)
	{
		wprintf((wformat(L"AcceptHandler - Error: %s\n") % error_code).str().c_str());
		return;
	}

	boost::asio::async_write(g_socket, boost::asio::buffer(g_data), WriteHandler);
}

void boost_example::WebServer()
{
	wprintf(L"*** Boost WebServer Example - Start\n");

	g_acceptor.listen();
	g_acceptor.async_accept(g_socket, AcceptHandler);
	wprintf(L"Server address: http://127.0.0.1:7777\n");
	g_io_service.run();

	wprintf(L"*** Boost WebServer Example - End\n\n");
}

