/*
 * thread.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "list.h"
#include "lock.h"
#include "system.h"
#include "SCHEDULE.H"
#include <iostream.h>
//#include "sleepL.h"

Thread::Thread(StackSize stackSize, Time timeSlice){
	myPCB=new PCB(stackSize, timeSlice, this);
	//cout<<"Thread made"<<endl;
}

Thread::~Thread(){
	waitToComplete();

	Lock::lock();

	//cout<<"Thread "<<getId()<<" ended";
	delete myPCB;
	myPCB=0;

	Lock::unlock();
}


void Thread::start(){
	Lock::lock();

	myPCB->startThread();

	Lock::unlock();
	//cout<<"Thread started"<<endl;
}

void Thread::waitToComplete(){
	Lock::lock();

	if(myPCB==0){
		Lock::unlock();
		return;
	}

	if(myPCB->status==FINISHED || myPCB==PCB::running || myPCB==System::idle->getPCB()){
		Lock::unlock();
		return;
	}

	/*if(myPCB->status==SLEEPING){
		Lock::unlock();
		return;
	}*/

	if(myPCB->status==NEW){
		Lock::unlock();
		return;
	}

	PCB::running->status=BLOCKED;
	myPCB->blockedThreads->pushPCB(PCB::running);

	Lock::unlock();
	//cout<<"Thread waitingToComplete"<<endl;

	dispatch();
}

void Thread::sleep(Time timeToSleep){
	PCB::running->sleep(timeToSleep);
}

ID Thread::getId(){
	Lock::lock();

	int id=myPCB->getID();

	Lock::unlock();

	return id;
}

void dispatch(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif

	PCB::wantDispatch=1;
	System::timer();

	//cout<<"Dispatching"<<endl;
#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif
}
