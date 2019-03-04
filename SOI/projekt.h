#include <stdio>
#include <cstdlib>
#incldue "monitor.h"


#define MAXSIZE 10
#define CONSUMERS 5
#define PRODUCERS 2
#define NUMBEROFBUFFS CONSUMERS


//buffer
class Buffer
{
    int count, stack[MAXSIZE];
    
	Buffer() {count = 0;}
    void pushItem(int item);
    int removeItem();
    void printBuffer();
    int sizeOfStack();
}
//monitor
class BufferMonitor: public Monitor
{
    Condition full, empty;
    Buffer buffer;
    void pushItem(int item);
    int readItem(BuffersMonitor &buffersMonitor);
    int getSize();
}
//Manage monitors
class BuffersMonitor: Monitor
{
    int emptyCount;
    Condition allEmpty;

    GroupMonitor() {emptyCount = MAXSIZE * CONSUMERS;}
    void findFreeSlotAndAdd(const int * tab, BufferMonitor *buff); //tab of monitorsl
    void up();
}

//////////////////////////////////////////////////////

void Buffer::pushItem(int item)
{
    stack[count++] = item;
}
int Buffer::removeItem()
{
    return stack[--count];
}
void Buffer::printBuffer()
{
    std::cout<<"Buffer elements: ";
    for (int i = 0; i < count; i++)
        std::cout<<stack[i]<<' ';
    std::cout<<'\n';
}
int Buffer::sizeOfStack()
{
    return count;
}
////////////////////////////////////////////////////////////

void BufferMonitor::pushItem(int item)
{
    enter();
    while (buffer.sizeOfStack() == MAXSIZE)
        wait(empty);
    buffer.pushItem(item);
	buffer.printBuffer();
    if (buffer.sizeOfStack() == 1)
        signal(full);
    leave();
}
int BufferMonitor::readItem(BuffersMonitor &buffersMonitor)
{
    enter();
    while (buffer.sizeOfStack() == 0)
        wait(empty);
    int valueToReturn = buffer.removeItem();
	buffer.printBuffer();
    if (buffer.sizeOfStack() == MAXSIZE - 1)
        signal(empty);
    leave();
    buffersMonitor.up();// signal for allBuffersMonitor to
    return valueToReturn;// increment its count of freeSlots
}
int BufferMonitor::getSize()
{
    enter();
    int size = buffer.sizeOfStack();
    leave();
    return size;
}

///////////////////////////////////////////////////////////////

void BuffersMonitor::findFreeSlotAndAdd(int producerID, BufferMonitor *buff) //tab of monitors
{
    enter();
    while (emptyCount == 0)
        wait(allEmpty);
    int i = rand() % NUMBEROFBUFFS;
    while (buff[i].getSize() == MAXSIZE)//searching for free slot
        i = (i + 1) % NUMBEROFBUFFS;
    std::cout<<producerID<<" put item in "<<i<<" buffer.\n";
    buff[i].pushItem(rand() % 50);
    emptyCount--;
    leave();
}

void BuffersMonitor::up()
{
    enter();
    emptyCount++;
    leave();
}
//////////////////////////////////////////////////////////////////
