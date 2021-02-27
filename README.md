# SyncThreads
An example of synced threads when they share large data
The credit goes to my great friend Sandeep Zechariah George (sandeepzgk)
Instead of using mutex or normal circle buffers, in controller codes we only need the latest arrived data (We don't need the buffer). 
This code shows an example where the write thread write on the shared location and the read thread reads from it. There are three cells and the read thread always reads the latest arrived data.  
There are two verison of the same code:

-- sync.cpp uses global atomic variables

-- sync_ref.cpp uses references to the atomic varibales


to build it:
g++ -std=c++11 sync.cpp -o sync
