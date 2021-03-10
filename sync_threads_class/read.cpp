#include "read.hpp"

void read::GetParam(int * _buffer, std::atomic<short>* _available, std::atomic<bool>* _NewFrame, bool* _running){
    buffer = _buffer;
    available = _available;
    NewFrame =  _NewFrame;
    running = _running;
    read_loc = 2;
};
void read::Run(){
	while(*running){
		if ((*NewFrame).load()){
			temp = *available;
			*available = read_loc;
			read_loc = temp;
			std::cout << *(buffer + read_loc) << std::endl; 
			*NewFrame = false;
			std::this_thread::sleep_for(std::chrono::microseconds(1));  //This is an artificial delay 
		}
		else{
			std::cout << "No frame to read!" << std::endl;
		} 
	}
};