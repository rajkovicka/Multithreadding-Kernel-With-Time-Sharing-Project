/*
 * lock.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "lock.h"
#include "pcb.h"
#include <iostream.h>

int Lock::lockFlag=0;

void Lock::lock(){
	Lock::lockFlag=1;
	//cout<<"Locking"<<endl;
}

void Lock::unlock(){
	Lock::lockFlag=0;
	//cout<<"Unlocking"<<endl;
	if(PCB::wantDispatch==1){
		//cout<<"Someone wants dispatch"<<endl;
		dispatch();
	}
}


