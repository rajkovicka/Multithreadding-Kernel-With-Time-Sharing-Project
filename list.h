/*
 * list.h
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

#include "thread.h"

class PCB;

class List{

	struct Elem{
		PCB* pcb;
		Elem* next;
		Elem(PCB* p):pcb(p),next(0){}
	};

	int listSize;
	Elem *head,*tail;

public:

	List();
	~List();
	void pushPCB(PCB* pcb);
	void deleteFromList(PCB* pcb);
	int getSize() const;
	PCB* getFirst();

};

#endif /* LIST_H_ */
