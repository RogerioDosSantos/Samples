
#include <boost/signals2/mutex.hpp>

namespace boost_example
{
	void Thread();

	class CallableObject
	{
	public:
		CallableObject();
		~CallableObject();

	public:
		virtual void operator()(); // Callable object to start/stop thread execution

	private:
		boost::signals2::mutex _mutex_test;
	};
}