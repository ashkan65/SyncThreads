#include "write.hpp"

void write::GetParam(int * _buffer, std::atomic<short>* _available, std::atomic<bool>* _NewFrame, bool* _running){
    buffer = _buffer;
    available = _available;
    NewFrame =  _NewFrame;
    running = _running;
    write_loc = 1;
};
void write::Run(){
	for(int i = 1; i<20;i++){
		temp = *available;
		*available = write_loc;
		write_loc = temp;	
		*(buffer + write_loc) = i ; 
		*NewFrame = true;
		std::this_thread::sleep_for(std::chrono::microseconds(10));  //This is an artificial delay
	}
	*running = false;
};