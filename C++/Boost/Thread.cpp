
#include "./Thread.h"

#include <stdio.h>
#include <boost/format.hpp>
#include <boost/thread.hpp> 
#include <boost/signals2/mutex.hpp>

using boost_example::CallableObject;
using boost::wformat;
using boost::thread;

CallableObject::CallableObject()
{

}

CallableObject::~CallableObject()
{

}

void CallableObject::operator()()
{
	_mutex_test.lock();

	boost::thread::id id = boost::this_thread::get_id();
	wprintf((wformat(L"[ID: %d] - Thread Execution (Object) - Start.\n") % id).str().c_str());
	boost::this_thread::sleep_for(boost::chrono::milliseconds(1000));
	wprintf((wformat(L"[ID: %d] - Thread Execution (Object) - End.\n") % id).str().c_str());

	_mutex_test.unlock();
}

void CallableFunction()
{
	boost::thread::id id = boost::this_thread::get_id();
	wprintf((wformat(L"[ID: %d] - Thread Execution (Function) - Start.\n") % id).str().c_str());
	boost::this_thread::sleep_for(boost::chrono::milliseconds(500));
	wprintf((wformat(L"[ID: %d] - Thread Execution (Function) - End.\n") % id).str().c_str());
}

void boost_example::Thread()
{
	wprintf(L"*** Boost Thread Example - Start\n");

	CallableObject callable_object;
	thread object_thread(boost::ref(callable_object));
	thread function_thread(CallableFunction);
	thread object_thread1(boost::ref(callable_object));
	thread function_thread1(CallableFunction);

	wprintf(L"Waiting for the new thread execution to be finalized.\n");
	object_thread.join();
	function_thread.join();
	object_thread1.join();
	function_thread1.join();
	wprintf(L"New thread execution was finalized.\n");

	wprintf(L"*** Boost Thread Example - End\n\n");
}