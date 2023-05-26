/*
 * general.h
 *
 *  Created on: Sep 18, 2021
 *      Author: OS1
 */


#ifndef GENERAL_H_
#define GENERAL_H_


int syncPrintf(const char *format, ...);
int userMain(int argc, char** argv);
void dispatch();
void timerr();
void load();
void unload();




#endif /* GENERAL_H_ */
