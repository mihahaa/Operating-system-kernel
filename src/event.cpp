/*
 * event.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#include"event.h"
#include"kev.h"
#include"ivten.h"

void Event::signal()
{
	if (myImpl)
	myImpl->signal();
	return;
	}

void Event::wait()
{
	if (myImpl)
	myImpl->wait();
	return;
}
Event::Event(IVTNo i)
{
	myImpl=new KernelEv(i);

	}

Event::~Event()
{
	delete myImpl;
	myImpl=0;
	}
