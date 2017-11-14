// Application Entrypoint

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

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
        desc.add_options()("help", "Print help messages");

        po::variables_map vm;
        try
        {
            po::store(po::parse_command_line(argc, argv, desc), vm);  // can throw
            if (vm.count("help"))
            {
                std::cout << "Basic Command Line Parameter App" << std::endl << desc << std::endl;
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
