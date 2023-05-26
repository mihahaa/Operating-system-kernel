/*
 * pcb.h
 *
 *  Created on: Sep 16, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

#include"thread.h"




class PCBList;

class PCB{
	public:
	enum Status {
			NEW, BLOCKED, READY, FINISHED, BUSYWAIT, SIGNAL
		};
		unsigned ss,sp,bp;
		int status;
		Time timeslice;
		virtual ~PCB();
		PCB();
		PCB(Thread *t,StackSize sts,Time ts);
		static PCB *getpcbid(ID i);
		static volatile PCB *running;
		PCBList *cekajuci;
		void waitToComplete();
		void start();
		Thread* getowner();
		static ID getrunid();
		static PCBList* svi;
		ID id;
		ID getid();
		static void wrapper();
		Thread* owner;
		StackSize size;
protected:
		void run();


	private:
	static int trenutniid;
	unsigned *stack;
	void createStack();
};







#endif /* PCB_H_ */
