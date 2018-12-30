#include "Buffer.cpp"
#define NUMBEROFBUFFS 5
#define MAXSIZE 10
#define MAXITEMSINBUFFFS NUMBEROFBUFFS * MAXSIZE
class Buffers: Buffer{
	Buffer* buffers[NUMBEROFBUFFS];
	condition allFull, canRead[NUMBEROFBUFFS];
	int counterOfElements;
	
	
	
	void producer(int producerID);{
		enter();
		while(counterOfElements < MAX){
			std::cout<<"Producer "<<producerID<<"is waiting for free space"<<'\n';
			wait(allFull);
		}
		int buffN = rand() % NUMBEROFBUFFS;
		while((buffers[buffN]->count == MAXSIZE)){
			buffN++;
			buffN = buffN % NUMBEROFBUFFS;
		}
		std::cout<<"Producer "<<producerID<<"is entering buffer "<<buffN<<'\n';
		buffers[buffN]->pushItem(producerID);
		if(buffers[buffN]->count == 1)
			signal(canRead[buffN]);
		leave();
	}
	
	void consumer(int consumerNumber){
		enter();
		while(((buffers[consumerNumber])->counter) == 0)
			wait(canRead[consumerNumber]);
		
		(buffers[consumerNumber])->readItem();
		counterOfElements--;
		if(counterOfElements == (MAXITEMSINBUFFFS - 1))
			signal(allFull);
		leave();
	}
};