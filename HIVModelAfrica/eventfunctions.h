//////////////////////////////////////////////////////////
//    eventfunction.h                                  //
//    Created by Mikaela Smit on 07/11/2014.       	   //
//    Copyright (c) 2014 Mikaela Smit. All rights reserved.    //
//    These event are added to the EventQ.			   //
/////////////////////////////////////////////////////////

#include <stdio.h> 
#include "person.h"

using namespace std;


//// ---- NOTE: Think about having different types of events ----

	//// --- Demographic Events ---
	void EventMyDeathDate(person *MyPointerToPerson);			// Function to be executed upon death
	void EventBirth(person *MyPointerToPerson);					// Function to be executed when someone gives birth
	
	
	//// --- Calendar Events ---
	void EventTellNewYear(person *MyPointerToPerson);			// Tell us when a new year start an update calendar-related items
	
	
	//// --- HIV Events ---
	void EventMyHIVInfection(person *MyPointerToPerson);       // Function executed once person gets infecte with HIV
	void EventCD4change(person *MyPointerToPerson);			   // Function executed when CD4 count is due to change (go down)
    void EventARTCatSwitch(person *MyPointerToPerson);         // Function to switch people from Kids ART cat to Adult ART cat


    //// --- NCD Events ---
    void EventMyHyptenDate(person *MyPointerToPerson);			// Function executed when person develops hypertension
    void EventMyDepressionDate(person *MyPointerToPerson);		// Function executed when person develops depression
    void EventMyAsthmaDate(person *MyPointerToPerson);			// Function executed when person develops asthma
    void EventMyStrokeDate(person *MyPointerToPerson);			// Function executed when person develops hypertension
    void EventMyDiabetesDate(person *MyPointerToPerson);        // Function executed when person develops diabetes

    void EventMyBreastDate(person *MyPointerToPerson);          // Function executed when person develops breast cancer
    void EventMyCervicalDate(person *MyPointerToPerson);        // Function executed when person develops Cervical cancer
    void EventMyColoDate(person *MyPointerToPerson);            // Function executed when person develops Colorectum cancer
    void EventMyLiverDate(person *MyPointerToPerson);			// Function executed when person develops liver cancer
    void EventMyOesoDate(person *MyPointerToPerson);            // Function executed when person develops Oesophageal cancer
    void EventMyProstateDate(person *MyPointerToPerson);		// Function executed when person develops prostate cancer
    void EventMyOtherCanDate(person *MyPointerToPerson);        // Function executed when person develops other cancers

    void EventMyCKDDate(person *MyPointerToPerson);             // Function executed when person develops CKD


  