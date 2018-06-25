/*
 * idle.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "idle.h"
#include "thread.h"
#include "pcb.h"
#include "lock.h"
#include <iostream.h>

Idle::Idle():Thread(defaultStackSize, 1){}

Idle::~Idle(){
	waitToComplete();
}

void Idle::start(){
	Lock::lock();

	myPCB->createStack();
	myPCB->status=NEW;

	Lock::unlock();
}

PCB* Idle::getPCB(){
	return myPCB;
}

void Idle::run(){
	//cout<<"Idle running"<<endl;
	while(1){
	}
}

