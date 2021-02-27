#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector
#include <chrono>	  // TO add artificial delays. You can remove it. 

using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds




void read (int * a, std::atomic<short>* _available, std::atomic<bool>* _NewFrame, bool* _running) {
	short read_loc = 2;
	while(*_running){
		if ((*_NewFrame).load()){
			int temp = *_available;
			*_available = read_loc;
			read_loc = temp;
			std::cout << *(a + read_loc) << std::endl; 
			*_NewFrame = false;
			sleep_for(milliseconds(1));  //This is an artificial delay 

		}
		else{
			std::cout << "No frame to read!" << std::endl;
		} 
	}
};

void write (int * a, std::atomic<short>* _available, std::atomic<bool>* _NewFrame, bool* _running) {	
	short write_loc = 1;
	for(int i = 1; i<20;i++){
		int temp = *_available;
		*_available = write_loc;
		write_loc = temp;	
		*(a + write_loc) = i ; 
		*_NewFrame = true;
		sleep_for(microseconds(1000));  //This is an artificial delay
	}
	*_running = false;
};

int main ()
{
	std::atomic<short> available (0);
	std::atomic<bool> NewFrame (false);
	bool running = true;
	int a[3];  // The shared cells

std::thread t1(write, a, &available, &NewFrame, &running);
std::thread t2(read , a, &available, &NewFrame, &running);
t1.join();
t2.join();
  return 0;
}
