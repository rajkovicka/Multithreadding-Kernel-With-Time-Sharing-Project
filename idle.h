/*
 * idle.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class Idle : public Thread{

public:

	Idle();
	~Idle();
	void start();
	void run();
	PCB* getPCB();

};


#endif /* IDLE_H_ */
