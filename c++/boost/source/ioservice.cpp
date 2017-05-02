
#include "./IOService.h"

#include <stdio.h>
#include <boost/format.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>

using boost::wformat;
using boost::shared_ptr;

void WorkerThread(boost::shared_ptr<boost::asio::io_service> io_service)
{
	boost::thread::id id = boost::this_thread::get_id();
	wprintf((wformat(L"[ID: %d] - WorkerThread - Start.\n") % id).str().c_str());

	while (true)
	{
		try
		{
			//Non exception mode with error handling
			//boost::system::error_code error_code;
			//io_service->run(error_code);
			//if (error_code)
			//{
			//	wprintf((wformat(L"[ID: %d] - WorkerThread System Error - %s.\n") % id % error_code).str().c_str());
			//}

			io_service->run();
			break;
		}
		catch (std::exception & exception)
		{
			wprintf((wformat(L"[ID: %d] - WorkerThread Exceptions - %s.\n") % id % exception.what()).str().c_str());
		}
	}
	
	//io_service.poll(); //Assynchronous
	wprintf((wformat(L"[ID: %d] - WorkerThread - End.\n") % id).str().c_str());
}

void RaiseAnException()
{
	throw(std::runtime_error("Proposital Exception!"));
}

void WorkerFunction(int parameter)
{
	boost::thread::id id = boost::this_thread::get_id();
	wprintf((wformat(L"[ID: %d] - WorkerFunction (Parameter = %d) - Start.\n") % id % parameter).str().c_str());
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	wprintf((wformat(L"[ID: %d] - WorkerFunction (Parameter = %d) - End.\n") % id % parameter).str().c_str());
}

void TimerFunction(const boost::system::error_code& error_code, boost::shared_ptr<boost::asio::deadline_timer> timer, boost::shared_ptr<boost::asio::io_service::strand> strand, shared_ptr<int> max_count)
{
	boost::thread::id id = boost::this_thread::get_id();
	if (error_code)
	{
		wprintf((wformat(L"[ID: %d] - TimerFunction Error - %s.\n") % id % error_code).str().c_str());
		return;
	}
	
	wprintf((wformat(L"[ID: %d] - TimerFunction: Count = %d\n") % id % *max_count).str().c_str());
	if (*max_count > 0)
	{
		timer->expires_from_now(boost::posix_time::seconds(1));
		//We use the strand to assure that the timer will always be called in sequence. 
		//In this way we do not have to care about multi-thread protection. This does not means that will not be called by multiple threads.
		timer->async_wait(strand->wrap(boost::bind(&TimerFunction, _1, timer, strand, max_count)));
		--(*max_count);
	}

}


void boost_example::IOService()
{
	wprintf(L"*** Boost IOService Example - Start\n");
	
	boost::shared_ptr<boost::asio::io_service> io_service(new boost::asio::io_service());
	shared_ptr<boost::asio::io_service::work> work(new boost::asio::io_service::work(*io_service));

	boost::thread_group worker_threads;
	for (int index = 0; index < 3; ++index)
		worker_threads.create_thread(boost::bind(&WorkerThread, io_service));

	io_service->post(boost::bind(WorkerFunction, 1));
	io_service->post(boost::bind(WorkerFunction, 2));
	io_service->post(boost::bind(WorkerFunction, 3));
	io_service->dispatch(boost::bind(WorkerFunction, 4)); //Dispatch can be executed from the current worker thread even if there are other pending events

	//Using strand we can execute the things in sequence.
	//This can be usefull since items might not be accessed simultaniasly by 02 threads. 
	//Be carefull, this does not means only one thread will execute that but that this will be executed once per time.
	shared_ptr<boost::asio::io_service::strand> strand = shared_ptr<boost::asio::io_service::strand>(new boost::asio::io_service::strand(*io_service));
	strand->post(boost::bind(WorkerFunction, 10));
	strand->post(boost::bind(WorkerFunction, 11));
	strand->post(boost::bind(WorkerFunction, 12));
	strand->dispatch(boost::bind(WorkerFunction, 13)); //Dispatch can be executed from the current worker thread even if there are other pending events

	//Exceptions will be gotten on the same thread that called the run.
	io_service->post(&RaiseAnException);

	//Timer	
	boost::shared_ptr<boost::asio::deadline_timer> timer(new boost::asio::deadline_timer(*io_service));
	shared_ptr<int> max_count = shared_ptr<int>(new int(10));
	timer->expires_from_now(boost::posix_time::seconds(5));
	//It is vital to note how we must wrap the timer handler through the strand everywhere and not just the first time. 
	//If we forget that, the timer would no longer execute through the strand object and bugs can result.
	timer->async_wait(strand->wrap(boost::bind(&TimerFunction, _1, timer, strand, max_count)));

	work.reset(); //Stop the work execution
	//io_service->stop(); //Stop all executions

	worker_threads.join_all();
	wprintf(L"*** Boost IOService Example - End\n\n");
}
