/*
 * event.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "event.h"
#include "KernelEv.h"

Event::Event(IVTNo ivtNo){
	myImpl=new KernelEv(ivtNo, this);
}

Event::~Event(){
	delete myImpl;
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}


