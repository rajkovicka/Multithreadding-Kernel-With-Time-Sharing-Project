/*
 * pcb.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "pcb.h"
#include "SCHEDULE.H"
#include <dos.h>
#include "lock.h"
#include <stdio.h>
#include <iostream.h>
#include "sleepL.h"

ID PCB::uID=0;
List* PCB::allPCBs=0;
SleepList* PCB::sleepingPCBs=0;
PCB* PCB::running=0;
int PCB::wantDispatch=0;

PCB::PCB(StackSize stackSize, Time timeSlice, Thread *t){
	Lock::lock();

	size=stackSize;
	if(size>65536)
		size=65536;
	time=timeSlice;
	myThread=t;
	myID=++uID;
	myStack=0;
	bp=0;
	ss=0;
	sp=0;
	status=NEW;

	PCB::allPCBs->pushPCB(this);
	blockedThreads=new List();

	//cout<<"PCB made"<<endl;

	Lock::unlock();
}

PCB::~PCB(){
	if(myStack!=0){
		delete [] myStack;
		//cout<<"Deleting stack"<<endl;
	}

	delete blockedThreads;
	blockedThreads=0;

	//PCB::sleepingPCBs->deleteFromList(this);
	PCB::allPCBs->deleteFromList(this);
	//cout<<"PCB deleted"<<endl;
}

ID PCB::getID(){
	return myID;
}

void PCB::startThread(){
	if(status==NEW){
		status=READY;
		createStack();
		Scheduler::put(this);
		//cout<<"PCB scheduled"<<endl;
	}
}

void PCB::createStack(){
	size=size/2;
	unsigned* stack=new unsigned[size];

	stack[size-1]=0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[size-2]=FP_SEG(&(PCB::wrapper));
	stack[size-3]=FP_OFF(&(PCB::wrapper));
	myStack=stack;
	sp=FP_OFF(stack+size-12);
	ss=FP_SEG(stack+size-12);
#endif
	bp=sp;
	//cout<<"Stack made"<<endl;
}

void PCB::wrapper(){
	//cout<<"Initializing run"<<endl;
	PCB::running->myThread->run();
	//cout<<"Run done"<<endl;
	Lock::lock();

	PCB::running->status=FINISHED;

	PCB::running->wakeWaiting();
}

void PCB::sleep(Time timeToSleep){
	if(PCB::running->status!=FINISHED){
		Lock::lock();

		PCB::running->status=SLEEPING;
		//cout<<"Sleeping"<<PCB::running->getID()<<endl;
		PCB::sleepingPCBs->pushSleepPCB(PCB::running,timeToSleep);

		Lock::unlock();
		dispatch();
	}
}

void PCB::checkSleepList(){
	PCB::sleepingPCBs->checkSleepList();
}

void PCB::wakeWaiting(){
	Lock::lock();

	PCB *pcb;
	while((pcb=PCB::running->blockedThreads->getFirst())!=0){
		pcb->status=READY;
		Scheduler::put(pcb);
		//cout<<"Waking blocked"<<endl;
	}

	Lock::unlock();
	dispatch();
}
