/*
 * pomf.h
 *
 *  Created on: Sep 17, 2021
 *      Author: OS1
 */

#ifndef POMF_H_
#define POMF_H_



class bzvz;
class Thread;

typedef void interrupt(*InterruptRoutine)(...);

class pomf{
public:
	friend class Thread;
	static void _dispatch();
	static Thread* starting;
	static bzvz* idle;
	static  unsigned volatile counter;
	static volatile int demanded;
	static InterruptRoutine stara;
	static void postavi();
	static void raskloni();
	static volatile int locki;
};
void load();
void unload();
void interrupt timerr(...);



#endif /* POMF_H_ */
