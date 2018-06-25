/*
 * system.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "idle.h"

typedef void interrupt(*interruptRoutine)(...);

class System{

public:

	static int counter;
	static int oldWantDispatch;

	static Idle* idle;
	static interruptRoutine old;
	static void interrupt timer(...);

	static void inic();
	static void restore();

};

#endif /* SYSTEM_H_ */
