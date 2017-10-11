//////////////////////////////////////////////////////////////////
//    eventQ.cpp                                                //
//    Created by Mikaela Smit on 30/10/2014.					//
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.     //
//    This script is to make the EventQ itself.       		    //
//////////////////////////////////////////////////////////////////


#include "event.h" 
#include "eventQ.h"


//// --- OUTSIDE INFORMATION --- ////
bool timeComparison::operator()(const event *lhs, const event *rhs) const{
	return lhs->time > rhs->time;}
 	
//// --- CLASS (EVENTQ) CONSTRUCTOR --- ////
eventQ::eventQ()
{} 


