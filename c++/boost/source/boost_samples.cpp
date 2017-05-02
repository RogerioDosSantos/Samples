// Boost Samples Application Entrypoint

#include <boost/program_options.hpp>

#include <iostream>
#include <string>
// #include <signal.h>

#include "./timer.h"
#include "./thread.h"
#include "./serialization.h"
#include "./bind.h"
#include "./ioservice.h"
#include "./ioservicetcp.h"
#include "./webclient.h"
#include "./webserver.h"
#include "./parser.h"

using namespace boost_example;

namespace
{
    const size_t SUCCESS = 0;
    const size_t ERROR_IN_COMMAND_LINE = 1;
    const size_t ERROR_COULD_NOT_FORK_PROCESS = 2;
    const size_t ERROR_UNHANDLED_EXCEPTION = 2;

}  // namespace

int main(int argc, char** argv)
{
    // // Fork the process if it is a parent process
    // // signal(SIGCHLD, SIG_IGN); //ignoring SIGCHLD, to prevent zombie processes
    // pid_t process_id = fork();
    // std::cout << "Process ID:" << process_id << std::endl;
    // if (process_id < 0)
    // {
    //     std::cout << "Failed to fork process" << std::endl;
    //     return ERROR_COULD_NOT_FORK_PROCESS;
    // }
    //
    // if (process_id != 0)
    //     return SUCCESS;  // Parent Process

    try
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
            ("help", "Print help messages")
            ("timer", "Timer example")
            ("thread", "Thread example")
            ("serialization", "Serialization example")
            ("bind", "Bind example")
            ("ioservice", "Ioservice example")
            ("ioservicetcp", "Ioservicetcp example")
            ("webclient", "Webclient example")
            ("webserver", "Webserver example")
            ("parser", "Parser example")
          ;

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);  // can throw
            if (vm.count("help"))
            {
                std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl;
                // std::cout << "Press any key to continue" << std::endl;
                // getchar();
                return SUCCESS;
            }

            if (vm.count("timer"))
            {
                Timer();
                return SUCCESS;
            }

            if (vm.count("thread"))
            {
              Thread();
              return SUCCESS;
            }

            if (vm.count("serialization"))
            {
              Serialization();
              return SUCCESS;
            }

            if (vm.count("bind"))
            {
              Bind();
              return SUCCESS;
            }

            if (vm.count("ioservice"))
            {
              IOService();
              return SUCCESS;
            }

            if (vm.count("ioservicetcp"))
            {
              IOServiceTCP();
              return SUCCESS;
            }

            if (vm.count("webclient"))
            {
                WebClient();
                return SUCCESS;
            }

            if (vm.count("webserver"))
            {
                WebServer();
                return SUCCESS;
            }

            if (vm.count("parser"))
            {
              Parser();
              return SUCCESS;
            }

            po::notify(vm);  // throws on error, so do after help in case
        }
        catch (po::error& e)
        {
            std::cout << "ERROR: " << e.what() << std::endl << std::endl;
            std::cout << desc << std::endl;
            return ERROR_IN_COMMAND_LINE;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "Unhandled Exception reached the top of main: " << e.what() << ", application will now exit" << std::endl;
        return ERROR_UNHANDLED_EXCEPTION;
    }

    return SUCCESS;
}  // main
