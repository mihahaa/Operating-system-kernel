/*
 * pcb.cpp
 *
 *  Created on: Sep 16, 2021
 *      Author: OS1
 */

#include "pcb.h"
#include "pcblista.h"
#include <dos.h>
#include "pomf.h"
#include "SCHEDULE.H"
#include "thread.h"
#include<iostream.h>




volatile PCB* PCB::running=0;
PCBList* PCB::svi=new PCBList();
int PCB::trenutniid=0;
PCB* novi;

void PCB::start()
{
	pomf::locki--;
status=PCB::READY;
Scheduler::put(this);
pomf::locki++;
}

PCB::PCB(){
pomf::locki--;
	ss=0;
	sp=0;
	owner=0;
	size=0;
	bp=0;
	trenutniid++;
	id=trenutniid;
	stack=0;
	timeslice=5;
	status=PCB::NEW;
	cekajuci=new PCBList();
	if (svi)
	svi->put(this);
	pomf::locki++;
}
void PCB:: run(){}
PCB::PCB(Thread* t,StackSize sts,Time ts)
{
	pomf::locki--;
	owner=t;
	timeslice=ts;
	status=PCB::NEW;
	trenutniid++;
	id=trenutniid;
	size=sts;
	createStack();
	cekajuci=new PCBList();
	if(svi)
	svi->put(this);
	pomf::locki++;
	}
void PCB::createStack()
{
	if (size > 65536)
			size = 65536;
	size /= sizeof(unsigned);
		stack=new unsigned [size];
		stack[size-1]=0x200;
		#ifndef BCC_BLOCK_IGNORE
			stack[size-2] = FP_SEG(&(PCB::wrapper));
			stack[size-3] = FP_OFF(&(PCB::wrapper));


			sp = FP_OFF(stack+size-12);
			ss = FP_SEG(stack+size-12);
			bp=sp;
		#endif
	}
ID PCB::getid()
{
	return id;
	}
ID PCB::getrunid()
{
	return PCB::running->id;
	}
PCB::~PCB()
{

	delete stack;
	delete cekajuci;

	}


Thread* PCB::getowner()
{return owner;}


void PCB::waitToComplete()
{
	pomf::locki--;
	if (status==PCB::NEW) {pomf::locki++;return;}
	if (this==(PCB*)running ) {pomf::locki++;return;}
	if (status==PCB::FINISHED) {pomf::locki++;return;}
	if (owner==(Thread*)pomf::idle) {pomf::locki++;return;}
		running->status=PCB::BLOCKED;
		if (cekajuci)
		this->cekajuci->put((PCB*)running);
		pomf::locki++;
		dispatch();
	}


void PCB::wrapper()
{

	PCB::running->owner->run();
	pomf::locki--;
	running->status=PCB::FINISHED;
	if (running->cekajuci)
	while (PCB::running->cekajuci->length()>0)
	{
		 novi=running->cekajuci->get();
		novi->status=PCB::READY;
		Scheduler::put(novi);
	}
	pomf::locki++;
	dispatch();
	}

