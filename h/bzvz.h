/*
 * bzvz.h
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */

#ifndef BZVZ_H_
#define BZVZ_H_

#include"thread.h"
#include<iostream.h>
class bzvz:public Thread{

public:
	bzvz();
	virtual void run();
};



#endif /* BZVZ_H_ */
