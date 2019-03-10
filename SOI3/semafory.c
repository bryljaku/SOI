#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define CONSUMER 5
#define PRODUCER 2
#define QUEUE 10
#define CONSUMERSLEEPTIME rand() % 1
#define PRODUCERSLEEPTIME rand() % 2
#define ITEMSCOUNTER queue[queueN][0]
#define MAXITEM 30


pthread_t consumers[CONSUMER], producers[PRODUCER];
sem_t mutex[CONSUMER], full[CONSUMER], empty[CONSUMER], allEmpty, allEmptyMutex;
int queue[CONSUMER][QUEUE + 1];// at index 0  we store number of items in queue

void showQueue(int queueN)
{
    if(ITEMSCOUNTER == 0) printf("Queue %d is empty\n", queueN);
    else
    {
        printf("Queue %d:",queueN);
        for(int i = 1; i <= ITEMSCOUNTER; i++)
        {
            printf(" %d,", queue[queueN][i]);
        }
        printf("\n");
    }
}
void initializeQueueSemaphores()
{
    for(int i = 0; i < CONSUMER; i++)
    {
        sem_init(&mutex[i], 0, 1);
        sem_init(&empty[i], 0, QUEUE);
        sem_init(&full[i], 0, 0);
    }
    sem_init(&allEmpty,0,QUEUE * CONSUMER);
    sem_init(&allEmptyMutex,0,1);
}

void initializeQueueItemCounter()
{
    for(int i = 0; i < CONSUMER; i++)
    {
        queue[i][0] = 0;
    }
}

void initializeQueue()
{
    initializeQueueItemCounter();
    initializeQueueSemaphores();
}

void produceItem(int producer, int queueN)
{
    int product = producer + rand() % MAXITEM;
    queue[queueN][ITEMSCOUNTER+1] = product;
    ITEMSCOUNTER++;
    printf("Producer %d put %d into %d queue \n", producer, product, queueN);
    showQueue(queueN);
}

void* producer()
{
    int producerP = 0;
    int queueP;
    while(producerP < PRODUCER && !(pthread_equal(pthread_self(), producers[producerP])))
    producerP++;
    while(1)
    {
    	int queueP = 0;
    	sem_wait(&allEmpty);
    	sem_wait(&allEmptyMutex);
    	queueP = rand() % CONSUMER;
    	while(queue[queueP][0] >= 10) {queueP++; queueP = queueP % CONSUMER;}
        sem_wait(&empty[queueP]);
        sem_wait(&mutex[queueP]);
        produceItem(producerP, queueP);
        sem_post(&mutex[queueP]);
        sem_post(&full[queueP]);
        sem_post(&allEmptyMutex);
        // sleep(PRODUCERSLEEPTIME);
    }
}

void consumeItem(int queueN)
{
    int item  = queue[queueN][1];
    for(int i = 1; i <= ITEMSCOUNTER; i++) queue[queueN][i] = queue[queueN][i + 1];
    --ITEMSCOUNTER;
    printf("Consumer %d took %d from %d queue \n", queueN, item, queueN);
    showQueue(queueN);
}

void* consumer()
{
    int consumerC = 0;
    while(consumerC < CONSUMER && !(pthread_equal(pthread_self(), consumers[consumerC])))
    consumerC++;
    while(1)
    {
        sem_wait(&full[consumerC]);
        sem_wait(&mutex[consumerC]);
        consumeItem(consumerC);
        sem_post(&mutex[consumerC]);
        sem_post(&empty[consumerC]);
        sem_post(&allEmpty);
       sleep(CONSUMERSLEEPTIME + 1);
    }
}
int main()
{
    initializeQueue();
    for(int i = 0; i < PRODUCER; i++)
    {
        pthread_create(producers + i, NULL, &producer, NULL);
    }
    for(int i = 0; i < CONSUMER; i++)
    {
        pthread_create(consumers + i, NULL, &consumer, NULL);
    }

    for(int i = 0; i < PRODUCER; i++)
    {
        pthread_join(*(producers + i), NULL);
    }
    for(int i = 0; i < CONSUMER; i++)
    {
        pthread_join(*(consumers + i), NULL);
    }    return 0;
}

