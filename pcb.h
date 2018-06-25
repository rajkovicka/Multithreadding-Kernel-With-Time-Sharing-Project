/*
 * pcb.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include "thread.h"
#include "list.h"
#include "sleepL.h"

enum Status {NEW, READY, RUNNING, BLOCKED, SLEEPING, FINISHED};

class PCB{

public:

	friend class Thread;
	friend class SleepList;

	static ID uID;
	static PCB* running;
	static List* allPCBs;
	static SleepList* sleepingPCBs;
	static int wantDispatch;

	Thread* myThread;
	Time time;
	StackSize size;
	ID myID;
	Status status;
	List *blockedThreads;
	unsigned* myStack;
	unsigned int ss,sp,bp;

	PCB(StackSize stackSize, Time timeSlice, Thread* t);
	~PCB();

	ID getID();
	void startThread();
	void createStack();
	static void wrapper();
	static void wakeWaiting();
	static void sleep(Time timeToSleep);
	static void checkSleepList();

};

#endif /* PCB_H_ */
