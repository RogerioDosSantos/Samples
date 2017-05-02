
#include <stdio.h>
#include <boost/asio.hpp>
#include <boost/format.hpp>
#include <string>

namespace web_server_example
{
    class WebServer
    {
    public:
        WebServer();
        ~WebServer();

        void WriteHandler(const boost::system::error_code& error_code, std::size_t bytes_transferred);
        void AcceptHandler(const boost::system::error_code& error_code);
        bool Start();

    private:
        boost::asio::io_service _io_service;
        boost::asio::ip::tcp::endpoint _endpoint;
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::ip::tcp::socket _socket;
        std::string _data;
    };
}

namespace boost_example
{
    void WebServer();
}
