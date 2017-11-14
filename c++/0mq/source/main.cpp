// Application Entrypoint

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

#include "./request_reply_server.h"

namespace
{
  const size_t SUCCESS = 0;
  const size_t ERROR_IN_COMMAND_LINE = 1;
  const size_t ERROR_COULD_NOT_FORK_PROCESS = 2;
  const size_t ERROR_UNHANDLED_EXCEPTION = 3;
}

int main(int argc, char** argv)
{
    try
    {
        namespace po = boost::program_options;
        po::options_description desc("Options");
        desc.add_options()
          ("help", "Display this command help")
          ("request_reply_server", "Request / Reply (Server)")
          ("request_reply_client", "Request / Reply (Client)")
        ;

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);  // can throw
            if (vm.count("help"))
            {
                std::cout << "0QM examples" << std::endl << desc << std::endl;
                return SUCCESS;
            }

            if (vm.count("request_reply_server"))
            {
              zero_qm_example::RequestReplyServer();
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
}
