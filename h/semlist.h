/*
 * semlist.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef SEMLIST_H_
#define SEMLIST_H_

class KernelSem;


class SemList{
private:
	struct elem {
				public:
					KernelSem *sadrzaj;
					elem *sled;
					elem(KernelSem* p)
					{
						sadrzaj=p;
						sled=0;
					}
				};
public:
	void put(KernelSem* p);
	void deletesem(KernelSem* p);
	~SemList();
	SemList();
	int length();
	elem *head;
	elem *tail;
	elem *pom;
	int size;
	void kucg();




};



#endif /* SEMLIST_H_ */
