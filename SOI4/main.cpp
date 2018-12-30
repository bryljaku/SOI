#include <iostream>
#include "projekt.h"
#include <pthread.h>
#define CONSUMERS 5
#define PRODUCERS 2
#define BUFFERS CONSUMERS
#define MAXSIZE 10


BufferMonitor buffersTab[BUFFERS];
BuffersMonitor bigBrother;

void *Producer(void *producerID)
{
    int producerNumber = *((int*)producerID);
	while(1)
	{
		bigBrother.findFreeSlotAndAdd(producerNumber, buffersTab);
		sleep(1);
	}
}
void *Consumer(void *consumerID)
{
    int consumerNumber = *((int*)consumerID);
	while(1)
	{
		std::cout<<consumerNumber<<" took "<<buffersTab[consumerNumber - 1].readItem(bigBrother, consumerNumber)	
				 <<" from buffer \n";
		sleep(8);
	}
}
int main()
{
    int idTab[CONSUMERS];
    for(int i = 0; i < CONSUMERS; i++)
    idTab[i] = i + 1;
	pthread_t producers[PRODUCERS], consumers[CONSUMERS];
	for (int i = 0; i < CONSUMERS; i++)
		pthread_create(&consumers[i], NULL, Consumer, &idTab[i]);
	
	for (int i = 0; i < PRODUCERS; i++)
		pthread_create(&producers[i], NULL, Producer, &idTab[i]);

	sleep(60);

	for (int i = 0; i < CONSUMERS; i++)
		pthread_cancel(consumers[i]);
	
	for (int i = 0; i < PRODUCERS; i++)
		pthread_cancel(producers[i]);
	return 0;
}
