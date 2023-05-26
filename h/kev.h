/*
 * kev.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef KEV_H_
#define KEV_H_

#include"event.h"

class PCB;

class KernelEv

{
private:
	struct elem {
					public:
						int vr;
						int ima;
						elem()
						{
							vr=ima=0;
						}
					};
public:
	PCB* moja;
	elem *sem;
	IVTNo bru;
	KernelEv(IVTNo i);
	~KernelEv();
	void wait();
protected:
	void signal();
	friend class IVTEntry;
	friend class Event;

	};






#endif /* KEV_H_ */
