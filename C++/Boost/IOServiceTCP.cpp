
#include "./IOServiceTCP.h"

#include <stdio.h>
#include <boost/format.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>

using boost::wformat;
using boost::shared_ptr;

void WorkerThreadTcp(boost::shared_ptr<boost::asio::io_service> io_service)
{
	boost::thread::id id = boost::this_thread::get_id();
	wprintf((wformat(L"[ID: %d] - WorkerThreadTcp - Start.\n") % id).str().c_str());

	while (true)
	{
		try
		{
			io_service->run();
			break;
		}
		catch (std::exception & exception)
		{
			wprintf((wformat(L"[ID: %d] - WorkerThreadTcp Exceptions - %s.\n") % id % exception.what()).str().c_str());
		}
	}
	
	wprintf((wformat(L"[ID: %d] - WorkerThreadTcp - End.\n") % id).str().c_str());
}

void OnAsyncClientConnectionCallback(const boost::system::error_code & error_code, boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	boost::thread::id id = boost::this_thread::get_id();
	if (error_code)
	{
		wprintf((wformat(L"[ID: %d] - OnAsyncClientConnectionCallback - Error: %s\n") % id % error_code).str().c_str());
		return;
	}

	wprintf((wformat(L"[ID: %d] - OnAsyncClientConnectionCallback - Connected!\n") % id).str().c_str());
}

void OnAsyncServerConnectionAccepted(const boost::system::error_code & error_code, boost::shared_ptr<boost::asio::ip::tcp::socket> socket)
{
	boost::thread::id id = boost::this_thread::get_id();
	if (error_code)
	{
		wprintf((wformat(L"[ID: %d] - OnAsyncServerConnectionAccepted - Error: %s\n") % id % error_code).str().c_str());
		return;
	}

	wprintf((wformat(L"[ID: %d] - OnAsyncServerConnectionAccepted - Connection Accepted!\n") % id).str().c_str());
}

void boost_example::IOServiceTCP()
{
	wprintf(L"*** Boost IOServiceTCP Example - Start\n");
	
	boost::shared_ptr<boost::asio::io_service> io_service(new boost::asio::io_service());
	boost::shared_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(*io_service));
	boost::shared_ptr<boost::asio::io_service::strand> strand(new boost::asio::io_service::strand(*io_service));
	boost::thread_group worker_threads;
	for (int index = 0; index < 3; ++index)
		worker_threads.create_thread(boost::bind(&WorkerThreadTcp, io_service));

	//Socket can be used for client implementation (We connect a Server)
	wprintf(L"*** Boost IOServiceTCP Client Example - Start\n");
	shared_ptr<boost::asio::ip::tcp::socket> socket(new boost::asio::ip::tcp::socket(*io_service));
	try
	{
		//Getting the address
		std::string address(100, '\0');
		wprintf(L"Enter the desired address (E.g.: www.google.com):\n");
		scanf_s("%s", &address[0], address.size());

		//Getting the TCP address
		boost::asio::ip::tcp::resolver resolver(*io_service);
		boost::asio::ip::tcp::resolver::query query(address, boost::lexical_cast<std::string>(80));
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);
		boost::asio::ip::tcp::endpoint endpoint = *iterator;

		//Connecting Synchronously
		//wprintf((wformat(L" - Connecting Synchronously to: %s\n") % endpoint).str().c_str());
		//socket->connect(endpoint);

		//Connecting Asynchronously
		wprintf((wformat(L" - Connecting Asynchronously to: %s\n") % endpoint).str().c_str());
		socket->async_connect(endpoint, boost::bind(OnAsyncClientConnectionCallback, _1, socket));

		std::string temp(100, '\0');
		wprintf(L"Enter anything to continue:\n");
		scanf_s("%*s", &temp[0], address.size());
		wprintf(L"Thank you!\n");

	}
	catch (std::exception & exception)
	{
		wprintf((wformat(L" - IOServiceTCP Exception - %s.\n") % exception.what()).str().c_str());
	}

	wprintf(L"*** Boost IOServiceTCP Client Example - End\n");

	boost::system::error_code error_code;
	socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, error_code);
	socket->close(error_code);

	//Acceptor can be used for server implementation (We get connected)
	wprintf(L"*** Boost IOServiceTCP Server Example - Start\n");
	boost::shared_ptr<boost::asio::ip::tcp::acceptor> acceptor(new boost::asio::ip::tcp::acceptor(*io_service));
	try
	{
		boost::asio::ip::tcp::resolver resolver(*io_service);
		boost::asio::ip::tcp::resolver::query query("127.0.0.1", boost::lexical_cast<std::string>(7777));
		boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
		acceptor->open(endpoint.protocol());
		acceptor->set_option(boost::asio::ip::tcp::acceptor::reuse_address(false));
		acceptor->bind(endpoint);
		acceptor->listen(boost::asio::socket_base::max_connections);
		//On this example the server will not accept any more connections. 
		//This is because we only call async_accept once and only have one socket object
		acceptor->async_accept(*socket, boost::bind(OnAsyncServerConnectionAccepted, _1, socket));

		std::string temp(100, '\0');
		wprintf((wformat(L" - Listenning on: %s\nYou can run the command \"telnet localhost 7777\" to start a connection to the server\nType anything to shutdown the server!\n") % endpoint).str().c_str());
		scanf_s("%*s", &temp[0], temp.size());
		wprintf(L"Thank you!\n");
	}
	catch (std::exception & exception)
	{
		wprintf((wformat(L" - IOServiceTCP Exception - %s.\n") % exception.what()).str().c_str());
	}

	wprintf(L"*** Boost IOServiceTCP Server Example - End\n");

	work.reset();
	//io_service->stop(); //Stop all executions

	worker_threads.join_all();
	wprintf(L"*** Boost IOServiceTCP Example - End\n\n");
}