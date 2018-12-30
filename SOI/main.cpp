#include <iostream>
#include "projekt.h"
#include <pthread.h>
#define CONSUMERS 5
#define PRODUCERS 2
#define BUFFERS CONSUMERS
#define MAXSIZE 10


BufferMonitor buffersTab[BUFFERS];
BuffersMonitor bigBrother;

void *Producer(int producerID)
{
	while(1)
	{
		bigBrother.findFreeSlotAndAdd(producerID, buffersTab);
		sleep(2);
	}
}
void *Consumer(int consumerID)
{
	while(1)
	{
		std::cout<<consumerID<<" took "buffersTab[consumerID - 1].readItem()	
				 <<"from buffer \n";
		sleep(1);
	}
}
int main()
{
	pthread_t producers[PRODUCERS], consumers[CONSUMERS];
	for (int i = 0; i < CONSUMERS, i++)
		pthread_create(&consumers[i], NULL, Consumer, i);
	
	for (int i = 0; i < PRODUCERS; i++)
		pthread_create(&producers[i], NULL, Producer, i);
	
	for (int i = 0; i < CONSUMERS, i++)
		pthread_cancel(&consumers[i]);
	
	for (int i = 0; i < PRODUCERS; i++)
		pthread_cancel(&producers[i]);
	return 0;
}