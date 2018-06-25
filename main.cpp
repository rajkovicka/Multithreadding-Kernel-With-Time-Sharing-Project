/*
 * main.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "list.h"
#include "thread.h"
#include "pcb.h"
#include "system.h"
#include "lock.h"
#include "idle.h"
#include <iostream.h>
#include "kernelSe.h"
#include "semList.h"
#include "sleepL.h"

int userMain(int argc, char* argv[]);

PCB* mainPCB;

int main(int argc, char* argv[]){
	System::inic();
	KernelSem::allSems=new SemList();
	PCB::allPCBs=new List();
	PCB::sleepingPCBs=new SleepList();

	System::idle=new Idle();
	System::idle->start();
	mainPCB=new PCB(defaultStackSize,defaultTimeSlice,0);

	PCB::running=mainPCB;
	PCB::running->status=RUNNING;

	Lock::lockFlag=0;
	int result=userMain(argc,argv);

	//cout<<PCB::allPCBs->getSize()<<endl;
	//cout<<PCB::sleepingPCBs->getSize()<<endl;
	delete mainPCB;
	delete System::idle;
	delete PCB::allPCBs;
	delete PCB::sleepingPCBs;
	delete KernelSem::allSems;

	System::restore();

	cout<<"Radi breeee!"<<endl;

	return result;
}


