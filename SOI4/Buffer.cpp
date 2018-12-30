


































/*#include <stdio>
#include <cstdlib>
#incldue "monitor.h"



#define MAXSIZE 10
#define CONSUMERS 5
#define PRODUCERS 2
#define NUMBEROFBUFFS CONSUMERS

class Buffer{
	int count, queue[MAXSIZE];
	
	Buffer(){
		count = 0;
	}
	void pushItem(int item)
	{
		queue[count] = item;
		count++;
	}
	int removeItem()
	{
		count--;
		return queue[count];
	}
	void printBuffer()
	{
		std::cout<<"Buffer elements: "
		for(int i = 0; i < count; i++)
		{
			std::cout<<queue[i]<<' ';
		}
		std::cout<<'\n';
	}
}

class BufferMonitor: Monitor{
	Condition full, empty;
	int count, bufferID;
	int buffer[MAXSIZE];

	Buffer(): Monitor()
	{}
	
	void pushItem(int producerID){
		enter();
		while(count == MAXSIZE){
			std::cout<<"Producer "<<producerID<<"is waiting\n";
			wait(empty);
		}
		std::cout<<"Producer "<<producerID<<"produces\n";
		buffer[count] = produce();
		if((count == 1) 
			signal(full);
		leave();
	}
	void readItem(BuffersMonitor &buffersMonitor){
		enter();
		while(count == 0){
			std::cout<<"Consumer "<<bufferID<<"is waiting\n";
			wait(full);
		}
		std::cout<<"Consumer "<<bufferID<<"consumed"
				 <<buffer[0]<<'\n';				 ;
		for(int i = 0; i < count - 1; i++)
			buffer[i] = buffer[i + 1];
		
		count--;
		if(count == MAXSIZE - 1)
			signal(empty);
		leave();
		buffersMonitor.up();
	}
	int getSize(){
		enter();
		int size = count;
		leave();
		return size;
	}
}
class BuffersMonitor: Monitor{
int emptyCount;
Condition allEmpty;

GroupMonitor()
{
	emptyCount = MAXSIZE * CONSUMERS;
}
void findAndAdd(const int * tab, Buffer buff)
	enter();
	while(emptyCount == 0)
		wait(allEmpty);
	int i = rand() % NUMBEROFBUFFS;
	while (B)
	{
		
	}
	leave();
}

*/


