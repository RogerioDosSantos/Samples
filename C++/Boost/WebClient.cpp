
#include "./WebClient.h"

#include <stdio.h>
#include <string> 
#include <boost/format.hpp>
#include <boost/asio.hpp> 
#include <boost/array.hpp> 

using boost::wformat;

namespace web_client_example
{
	boost::asio::io_service g_io_service;
	boost::asio::ip::tcp::resolver g_resolver(g_io_service);
	boost::asio::ip::tcp::socket g_socket(g_io_service);
	boost::array<char, 4096> g_buffer;
}

using web_client_example::g_io_service;
using web_client_example::g_resolver;
using web_client_example::g_socket;
using web_client_example::g_buffer;

void ReadHandler(const boost::system::error_code& error_code, std::size_t bytes_transferred)
{
	if (error_code)
	{
		//An error will also happen in case there is no more item to be read.
		wprintf((wformat(L"ReadHandler - Error: %s\n") % error_code).str().c_str());
		return;
	}

	wprintf((wformat(L"ReadHandler - Data Start:\n%s\nReadHandler - Data End\n\n") % g_buffer.data()).str().c_str());
	g_socket.async_read_some(boost::asio::buffer(g_buffer), ReadHandler);
}

void ConnectHandler(const boost::system::error_code& error_code)
{
	if (error_code)
	{
		wprintf((wformat(L"ConnectHandler - Error: %s\n") % error_code).str().c_str());
		return;
	}

	boost::asio::write(g_socket, boost::asio::buffer("GET / HTTP 1.1\r\nHost: highscore.de\r\n\r\n"));
	g_socket.async_read_some(boost::asio::buffer(g_buffer), ReadHandler);
}

void ResolveHandler(const boost::system::error_code &error_code, boost::asio::ip::tcp::resolver::iterator resolver_iterator)
{
	if (error_code)
	{
		wprintf((wformat(L"ResolveHandler - Error: %s\n") % error_code).str().c_str());
		return;
	}

	g_socket.async_connect(*resolver_iterator, ConnectHandler);
}

void boost_example::WebClient()
{
	wprintf(L"*** Boost WebClient Example - Start\n");

	boost::asio::ip::tcp::resolver::query query("www.highscore.de", "80");
	g_resolver.async_resolve(query, ResolveHandler);
	g_io_service.run();

	wprintf(L"*** Boost WebClient Example - End\n\n");
}