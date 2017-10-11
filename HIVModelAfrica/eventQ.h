/////////////////////////////////////////////////////////////////
//    eventQ.h                                                 //
//    Created by Mikaela Smit on 30/10/2014.		           //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    This script is to make the EventQ itself.		           //
/////////////////////////////////////////////////////////////////



#include <stdio.h>	 						// Refers to C StandarD Input Output library - uses streams to operate with physical devices including keyboards
#include <queue>							// Needed for the priorityQ
#ifndef eventQ_h							
#define eventQ_h
using namespace std;


//// --- DEFINE THE COMPARISON CLASS AND DEFINE OPERATOR --- ////
struct timeComparison {bool operator()(const event *lhs, const event *rhs) const;};	


//// --- CREATING EVENTQ --- ////
class eventQ{
public:

	eventQ();								// Constructor

	};

#endif	




