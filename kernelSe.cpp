/*
 * kernelSe.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "kernelSe.h"
#include "pcb.h"
#include "lock.h"
#include "list.h"
#include "SCHEDULE.H"
#include "semList.h"
#include <iostream.h>
#include "semBList.h"

SemList* KernelSem::allSems=0;

KernelSem::KernelSem(int init, Semaphore* s){
	semValue=init;
	sem=s;
	blocked=new SemBlockList();
	allSems->pushSem(this);
}

KernelSem::~KernelSem(){
	if(blocked->size()==0)
		delete blocked;
	blocked=0;
	allSems->deleteFromList(this);
}

void KernelSem::wakeUp(){
	PCB *pcb;
	while(blocked->size()>0){
		pcb=blocked->getFirst();
		pcb->status=READY;
		Scheduler::put(pcb);
		//cout<<"Rescheduled"<<endl;
	}
}

int KernelSem::wait(int toBlock){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif

	int result=0;
	if(toBlock==0 && semValue<=0)
		result=-1;
	else{
		if(--semValue<0){
			PCB::running->status=BLOCKED;
			blocked->pushBlocked(PCB::running);
			result=1;
			//cout<<"Blocked"<<endl;
		}
	}

#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif

	return result;
}

void KernelSem::signal(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();
#endif

	if(semValue++<0){
		PCB* pcb=blocked->getFirst();
		if(pcb!=0){
			pcb->status=READY;
			Scheduler::put(pcb);
			//cout<<"Deblocked"<<endl;
		}
	}

#ifndef BCC_BLOCK_IGNORE
	asmUnlock();
#endif
}
