/*
 * system.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "system.h"
#include <dos.h>
#include "pcb.h"
#include "lock.h"
#include "SCHEDULE.H"
#include "idle.h"
#include <iostream.h>

extern void tick();
interruptRoutine System::old=0;
Idle* System::idle=0;
int System::counter=0;
volatile unsigned int tss=0;
volatile unsigned int tsp=0;
volatile unsigned int tbp=0;
int System::oldWantDispatch=0;
volatile unsigned oldTimerOFF, oldTimerSEG;

void System::inic(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();

	old=getvect(0x08);
	setvect(0x08,timer);

	asmUnlock();
#endif
	//cout<<"Initialized"<<endl;
}

void System::restore(){
#ifndef BCC_BLOCK_IGNORE
	asmLock();

	setvect(0x08,old);

	asmUnlock();
#endif
	//cout<<"Restored"<<endl;
}

void interrupt System::timer(...){
	//cout<<"Entered timer routine"<<endl;
	System::oldWantDispatch=PCB::wantDispatch;

	if(PCB::wantDispatch==0 && System::counter!=0){
		counter--;
		//cout<<"Decreasing timer"<<endl;
	}

	if(PCB::wantDispatch==0){
		PCB::checkSleepList();
		//cout<<"Sleep List checked"<<endl;
	}

	if(PCB::wantDispatch==0){
		tick();
		//cout<<"Ticking"<<endl;
	}

	if(Lock::lockFlag==0){
/*#ifndef BCC_BLOCK_IGNORE
		asmLock();
		cout<<"Entered because lockFlag==0"<<endl;
		asmUnlock();
#endif*/
		if((System::counter==0 && PCB::running->time!=0) || PCB::wantDispatch==1){
#ifndef BCC_BLOCK_IGNORE
			asm{
				mov tss, ss
				mov tsp, sp
				mov tbp, bp
			}
#endif

			PCB::running->ss=tss;
			PCB::running->sp=tsp;
			PCB::running->bp=tbp;

			if(PCB::running->status==READY || (PCB::running->status==RUNNING && PCB::running!=idle->getPCB())){
				PCB::running->status=READY;
				Scheduler::put(PCB::running);
				//cout<<"Rescheduled"<<endl;
			}

			PCB::running=Scheduler::get();
			if(PCB::running==0)
				PCB::running=idle->getPCB();

			tss=PCB::running->ss;
			tsp=PCB::running->sp;
			tbp=PCB::running->bp;
			PCB::running->status=RUNNING;

#ifndef BCC_BLOCK_IGNORE
			asm{
				mov ss, tss
				mov sp, tsp
				mov bp, tbp
			}
#endif

			counter=PCB::running->time;
			PCB::wantDispatch=0;
			//cout<<"Cntxt chng";
		}
	}
	else
		PCB::wantDispatch=1;
	if(System::oldWantDispatch==0){
		(*old)();
	}
}
