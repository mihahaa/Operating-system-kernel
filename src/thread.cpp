/*
 * thread.cpp
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#include <dos.h>
#include <stdlib.h>
#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.h"
#include "pcblista.h"
#include"pomf.h"
#include "iostream.h"



void Thread::start()
{
	myPCB->start();
}
 void Thread::waitToComplete()
 {
	 myPCB->waitToComplete();

 }
 PCB* Thread::getpcb()
 {
	 return myPCB;
 }

 Thread::~Thread()
 {
	 delete myPCB;
 }
 ID Thread::getId()
 {
	 return myPCB->id;
 }
  ID Thread::getRunningId()
  {
	  return PCB::getrunid();
  }

 Thread::Thread(StackSize sts,Time ts)
 {
 	 myPCB=new PCB(this,sts,ts);
  }
 Thread* Thread::getThreadById(ID id)
 {
	return PCB::svi->getpcbid(id)->getowner();
 }



void dispatch()
{
	pomf::_dispatch();
	}


