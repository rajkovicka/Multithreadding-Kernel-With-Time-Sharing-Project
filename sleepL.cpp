/*
 * sleepL.cpp
 *
 *  Created on: Jun 24, 2018
 *      Author: OS1
 */

#include "sleepL.h"
#include "pcb.h"
#include <iostream.h>
#include "SCHEDULE.H"

SleepList::SleepList(){
	head=0;
	tail=0;
	listSize=0;
}

SleepList::~SleepList(){
	Elem *curr=head;
	while(curr!=0){
		head=head->next;
		if(head==0)
			tail=0;
		PCB* pcb=curr->pcb;
		delete pcb;
		delete curr;
		curr=head;
	}
	listSize=0;
}

void SleepList::pushSleepPCB(PCB* pcb, Time time){
	Elem *elem=new Elem(pcb, time);
	if(head==0)
		head=elem;
	else
		tail->next=elem;
	tail=elem;
	listSize++;
	//cout<<"Sleepy PCB"<<endl;
}

void SleepList::deleteFromList(PCB* pcb){
	Elem *curr=head, *prev=0;
	while((curr->pcb!=pcb) && curr!=0){
		prev=curr;
		curr=curr->next;
	}
	if(curr!=0){
		if(prev==0){
			head=head->next;
			if(head==0)
				tail=0;
			delete curr;
		}
		else{
			prev->next=curr->next;
			if(tail==curr)
				tail=prev;
			delete curr;
		}
		listSize--;
		//cout<<"Out of the list"<<endl;
	}
}

int SleepList::getSize()const{
	return listSize;
}

void SleepList::checkSleepList(){
	Elem *curr=head;
	while(curr!=0){
		Elem* next=curr->next;
		if(curr->time>0)
			curr->time--;
		if(curr->time==0)
			wakeUpFromList(curr->pcb);
		curr=next;
	}
}

void SleepList::wakeUpFromList(PCB* p){
	p->status=READY;
	Scheduler::put(p);
	//cout<<"Awaken"<<endl;
	deleteFromList(p);
}
