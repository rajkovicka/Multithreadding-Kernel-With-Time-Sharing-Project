/*
 * KernelEv.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "KernelEv.h"
#include "IVTEntry.h"
#include "pcb.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo iv, Event* e){
	ivt=iv;
	event=e;
	myPCB=PCB::running;
	eventValue=0;
	if(IVTEntry::get(ivt))
		IVTEntry::get(ivt)->k=this;
}

KernelEv::~KernelEv(){
	if(IVTEntry::get(ivt))
		IVTEntry::get(ivt)->k=0;
	signal();
}

IVTNo KernelEv::ivtNo()const{
	return ivt;
}

void KernelEv::signal(){
	if(eventValue++<0){
		myPCB->status=READY;
		Scheduler::put(myPCB);
	}
	else
		eventValue=1;
}

void KernelEv::wait(){
	if(myPCB!=0 && myPCB==PCB::running){
		if(--eventValue<0){
			myPCB->status=BLOCKED;
			dispatch();
		}
	}
}


