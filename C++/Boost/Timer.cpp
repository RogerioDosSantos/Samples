
#include "./Timer.h"

#include <stdio.h>
#include <boost/format.hpp>
#include <boost/chrono.hpp>
#include <boost/thread.hpp> 

using boost::wformat;
using boost::posix_time::ptime;
using boost::date_time::microsec_clock;
using boost::posix_time::milliseconds;

void boost_example::Timer()
{
	wprintf(L"*** Boost Timer Example - Start\n");

	boost::posix_time::ptime timer;
	timer = microsec_clock<ptime>::universal_time();
	timer += milliseconds(10000);
	boost::posix_time::ptime t1 = microsec_clock<ptime>::universal_time();
	boost::chrono::milliseconds period(100);
	int last_time = -1;
	while (microsec_clock<ptime>::universal_time() <= timer)
	{
		boost::this_thread::sleep_for(period);
		boost::posix_time::time_duration diff = microsec_clock<ptime>::universal_time() - t1;
		if (last_time >= diff.total_seconds())
			continue;

		last_time = diff.total_seconds();
		wprintf((wformat(L"Passed %d seconds\n") % last_time).str().c_str());
	}

	wprintf(L"*** Boost Timer Example - End\n\n");
}