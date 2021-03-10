#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector
#include <chrono>	 	 // TO add artificial delays. You can remove it. 
#include <functional>	//std::mem_fn

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds

#include "read.hpp"
#include "write.hpp"

int main ()
{
	std::atomic<short> available (0);
	std::atomic<bool> NewFrame (false);
	bool running = true;
	int a[3];  // The shared cells
	read reader;
	write writer;
	reader.GetParam(a, &available, &NewFrame, &running);
	writer.GetParam(a, &available, &NewFrame, &running);
	std::thread t2(std::mem_fn(&write::Run), &writer);
	std::thread t1(std::mem_fn(&read::Run), &reader);
	t2.join();
	t1.join();

	return 0;
}