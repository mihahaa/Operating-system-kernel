/*
 * kersem.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_



class PCBSem;
class SemList;

class KernelSem
{
public:
	int val() const;
	int wait(unsigned int maxTimeToWait);
	void signal();
	KernelSem(int init=1);
	~KernelSem();
	void incvalue();
	PCBSem* nasemu;
	static SemList* svisem;


private:

	int value;

	};



#endif /* KERSEM_H_ */
