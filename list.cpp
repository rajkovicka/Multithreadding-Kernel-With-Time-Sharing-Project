/*
 * list.cpp
 *
 *  Created on: Jun 22, 2018
 *      Author: OS1
 */

#include "list.h"
#include "pcb.h"
#include <iostream.h>

List::List(){
	head=0;
	tail=0;
	listSize=0;
	//cout<<"List made"<<endl;
}

List::~List(){
	Elem *curr=head;
	while(curr!=0){
		head=head->next;
		if(head==0)
			tail=0;
		delete curr;
		curr=head;
	}
	listSize=0;
	//cout<<"List deleted"<<endl;
}

void List::pushPCB(PCB* pcb){
	Elem *elem=new Elem(pcb);
	if(head==0)
		head=elem;
	else
		tail->next=elem;
	tail=elem;
	listSize++;
	//cout<<"PCB pushed"<<endl;
}

void List::deleteFromList(PCB* pcb){
	Elem *curr=head, *prev=0;
	while((curr->pcb!=pcb) && curr!=0){
		prev=curr;
		curr=curr->next;
	}
	if(curr!=0){
		if(prev==0){
			head=head->next;
			if(head==0)
				tail==0;
			delete curr;
		}
		else{
			prev->next=curr->next;
			if(tail==curr)
				tail=prev;
			delete curr;
		}
		listSize--;
		//cout<<"PCB deleted"<<endl;
	}
}

PCB* List::getFirst(){
	if(head!=0){
		Elem* curr=head;
		head=head->next;
		if(head==0)
			tail==0;
		listSize--;
		PCB *pcb=curr->pcb;
		delete curr;
		//cout<<"Returning first"<<endl;
		return pcb;
	}
	else
		return 0;
}

int List::getSize()const{
	return listSize;
}
