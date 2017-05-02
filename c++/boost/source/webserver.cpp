
#include "./WebServer.h"

#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/format.hpp>
#include <string>

using boost::wformat;
using web_server_example::WebServer;

WebServer::WebServer()
    : _io_service()
    , _endpoint(boost::asio::ip::tcp::v4(), 7777)
    , _acceptor(_io_service, _endpoint)
    , _socket(_io_service)
{
    // _data = "HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!";
    _data =
        "\r\n"
        "{\r\n"
        "  \"historian data\" : \r\n"
        "    {\r\n"
        "      \"id\" : 001, \r\n"
        "      \"time stamp\" : \"2016-12-31 23:59:59\", \r\n"
        "      \"values\": \r\n"
        "        {\r\n"
        "          \"tags\" : \r\n"
        "            [\r\n"
        "              {\r\n"
        "                \"name\" : \"real_tag\", \r\n"
        "                \"value\" : 123.3224\r\n"
        "              }, \r\n"
        "              {\r\n"
        "                \"name\" : \"string_tag\", \r\n"
        "                \"value\" : \"This is the string tag value\"\r\n"
        "              },\r\n"
        "              {\r\n"
        "                \"name\" : \"boolean_tag\", \r\n"
        "                \"value\" : true\r\n"
        "              }\r\n"
        "            ]\r\n"
        "        }\r\n"
        "    }\r\n"
        "}";
}

WebServer::~WebServer()
{
}

void WebServer::WriteHandler(const boost::system::error_code& error_code, std::size_t bytes_transferred)
{
    wprintf(L"WriteHandler - Start\n");
    if (error_code)
    {
        wprintf((wformat(L"WriteHandler - Error: %s\n") % error_code).str().c_str());
        return;
    }

    wprintf((wformat(L"WriteHandler - Transfered %d bytes\n") % bytes_transferred).str().c_str());
    wprintf(L"WriteHandler - End\n");
}

void WebServer::AcceptHandler(const boost::system::error_code& error_code)
{
    wprintf(L"AcceptHandler - Start\n");
    if (error_code)
    {
        wprintf((wformat(L"AcceptHandler - Error: %s\n") % error_code).str().c_str());
        return;
    }

    // boost::asio::async_write(_socket, boost::asio::buffer(_data), boost::bind(&WebServer::WriteHandler, this, _1, _2));
    boost::asio::async_write(_socket, boost::asio::buffer(_data), boost::bind(&WebServer::WriteHandler, this, _1, _2));
    wprintf(L"AcceptHandler - End\n");
}

bool WebServer::Start()
{
    _acceptor.listen();
    _acceptor.async_accept(_socket, boost::bind(&WebServer::AcceptHandler, this, _1));
    wprintf(L"Server address: http://127.0.0.1:7777\n");
    _io_service.run();
    return true;
}

void boost_example::WebServer()
{
    wprintf(L"*** Boost WebServer Example - Start\n");

    web_server_example::WebServer server;
    server.Start();

    wprintf(L"*** Boost WebServer Example - End\n\n");
}
