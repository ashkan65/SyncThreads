#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector
#include <chrono>
// #include<unistd.h>
// unsigned int microsecond = 10000;
using namespace std::this_thread; // sleep_for, sleep_until
using namespace std::chrono; // nanoseconds, system_clock, seconds


std::atomic<short> available (0);
std::atomic<bool> NewFrame (false);
short read_loc = 2;
short write_loc = 1;
bool running = true;

void read (int * a) {
	while(running){
	// for(int i = 1; i<10;i++){
		if (NewFrame.load()){
			int temp = available;
			available = read_loc;
			read_loc = temp;
			std::cout << *(a + read_loc) << std::endl; 
			NewFrame = false;
			sleep_for(milliseconds(1));

		}
		else{
			std::cout << "No frame to read!" << std::endl;
		} 
	}
};

void write (int * a) {	
	for(int i = 1; i<20;i++){
		int temp = available;
		available = write_loc;
		write_loc = temp;	
		*(a + write_loc) = i ; 
		NewFrame = true;
		sleep_for(microseconds(1500));
		// usleep(1 * microsecond);
	}
	running = false;
};

int main ()
{
int a[3];
std::thread t1(write, a);
std::thread t2(read, a);
t1.join();
t2.join();


  return 0;
}
