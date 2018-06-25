/*
 * event.h
 *
 *  Created on: Jun 23, 2018
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

typedef unsigned char IVTNo;
class KernelEv;

class Event{

public:

	Event(IVTNo ivtNo);
	~Event();
	void wait();

protected:

	friend class KernelEv;
	void signal();

private:

	KernelEv* myImpl;

};



#endif /* EVENT_H_ */
