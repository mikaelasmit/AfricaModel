/////////////////////////////////////////////////////////////////
//    LoadParams.h                                             //
//    Created by Mikaela Smit on 29/10/2015.				   //
//    Copyright (c) 2015 Mikaela Smit. All rights reserved.    //
//    Loads arrays and parameters from txt file                //
/////////////////////////////////////////////////////////////////


#ifndef ____LoadParams__
#define ____LoadParams__


//// --- External Large Arrays --- ////
void loadBirthArray();								// functions to load arrays
void loadDeathArray_Women();
void loadDeathArray_Men();
void loadHIVArray_Women();
void loadHIVArray_Men();
void loadNCDArray();
void loadCancerArray();


//// --- Shorter Parameter Arrays from txt file --- ////

void loadCD4StartArray();
void loadCD4ProgArray();
void loadCD4DeathArray();
void loadCD4ARTArray();

void loadNrChildren();
void loadNrChildrenProb();
void loadAgeDistribution();
void loadAgeMin();
void loadAgeMax();

void loadNCDAgeArrayMin();
void loadNCDAgeArrayMax();

void loadCancerAgeArrayMin();
void loadCancerAgeArrayMax();




#endif /* defined(____LoadParams__) */
