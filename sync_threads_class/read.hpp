#include <iostream>       // std::cout
#include <atomic>         // std::atomic, std::atomic_flag, ATOMIC_FLAG_INIT
#include <thread>         // std::thread, std::this_thread::yield
#include <vector>         // std::vector
#include <chrono>	  // TO add artificial delays. You can remove it. 


class read{
	private:
        int* buffer;
        std::atomic<short>* available;
        std::atomic<bool>* NewFrame;
        bool* running;
        short read_loc;
        int temp;
        
    public:
        void GetParam(int * _buffer, std::atomic<short>* _available, std::atomic<bool>* _NewFrame, bool* _running);
        void Run();
};