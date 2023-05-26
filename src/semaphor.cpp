/*
 * semaphor.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#include"semaphor.h"
#include"kersem.h"
#include<iostream.h>


 Semaphore::Semaphore (int init)
 {
	 myImpl=new KernelSem(init);
 }
  Semaphore::~Semaphore()
 {
	 delete myImpl;
 }
void Semaphore::signal()
{
	myImpl->signal();
}
int Semaphore::wait(Time maxTimeToWait) {
	return myImpl->wait(maxTimeToWait);
}

int Semaphore::val() const {
	return myImpl->val();
}

