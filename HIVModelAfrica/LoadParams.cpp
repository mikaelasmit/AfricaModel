/////////////////////////////////////////////////////////////////
//    LoadParams.cpp                                           //
//    Created by Mikaela Smit on 29/10/2015.				   //
//    Copyright (c) 2015 Mikaela Smit. All rights reserved.    //
//    Loads arrays and parameters from txt file                //
/////////////////////////////////////////////////////////////////


#include <iostream>
#include <fstream>										
#include <sstream>
#include <string>
#include <vector>
#include "errorcoutmacro.h"
#include "CParamReader.hpp"
#include "LoadParams.h"

using namespace std;


//// --- Pointers to external arrays --- ////

// Big Arrays
double** BirthArray;
double** DeathArray_Women;
double** DeathArray_Men;
double** HIVArray_Women;
double** HIVArray_Men;
double** NCDArray;
double** CancerArray;

// HIV Arrays
double*** CD4_startarray;
double**  CD4_prog_rates;
double*** Death_CD4_rates;
double*** ART_CD4_rates;

// Demographic Arrays
double**  NrChildrenArray;
double*   NrChildrenProb;
double**  Age1950Array;
int*      ArrayMin;
int*      ArrayMax;

// NCD Arrays
int nr_NCDs=6;                                         // Change this as you need to
int nr_Cancers=7;

extern string ParamDirectory;



////////////////////////////////////////////////////////
/////// --- READ IN KEY PARAMETERS FROM FILE --- ///////
////////////////////////////////////////////////////////

//// --- Load parameters --- ////
void loadCD4StartArray(){
    
    E(cout<< "The CD4_startarray Parameter is being loaded" << endl;)
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "CD4_startarray";                // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl << " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int levels=2;
    int row=nr_rows/2;
    int col=nr_columns;

    
    // Lets make the *** Array
    CD4_startarray = new double **[levels];
    for (int i=0; i<levels; i++)
        {CD4_startarray[i] = new double *[row];}
    for (int i=0; i<levels; i++)
        {for (int j=0; j<row; j++)
            {CD4_startarray[i][j] = new double [col];}}
    
    for (int l=0; l<levels; l++){
        for (int j=0; j<row; j++){
            for (int i=0; i<col; i++){
                int NElement=i+(j*col)+(l*row*col);
                CD4_startarray[l][j][i]=data[NElement];
                //cout << "L: " << l << " J: " << j << " and i: " << i << endl;
                //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and CD4_array " << CD4_startarray[l][j][i] << endl;
            }
        }
    }
    E(cout<< "The CD4_startarray Parameter has been loaded" << endl;)
}



void loadCD4ProgArray()
{
    E(cout<< "The CD4_prog_rates Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "CD4_prog_rates";                // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int row=nr_rows;
    int col=nr_columns;
    
    
    // Lets make the *** Array
    CD4_prog_rates = new double *[row];
    for (int i=0; i<row; i++)
        {
            CD4_prog_rates[i] = new double [col];
        }
    
    for (int j=0; j<row; j++){
        for (int i=0; i<col; i++){
            int NElement=i+(j*col);
            CD4_prog_rates[j][i]=data[NElement];
            //cout << "J: " << j << " and i: " << i << " NElement: " << NElement << endl;
            //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and CD4_prog_rates " << CD4_prog_rates[j][i] << endl;
        }
    }
    E(cout<< "The CD4_prog_rates Parameter has been loaded" << endl;)
}



void loadCD4DeathArray()
{
    E(cout<< "The CD4_death_rates Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "CD4_death_rates";               // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int levels=2;
    int row=nr_rows/2;
    int col=nr_columns;
    
    
    // Lets make the *** Array
    Death_CD4_rates = new double **[levels];
    for (int i=0; i<levels; i++)
    {Death_CD4_rates[i] = new double *[row];}
    for (int i=0; i<levels; i++)
    {for (int j=0; j<row; j++)
    {Death_CD4_rates[i][j] = new double [col];}}
    
    for (int l=0; l<levels; l++){
        for (int j=0; j<row; j++){
            for (int i=0; i<col; i++){
                int NElement=i+(j*col)+(l*row*col);
                Death_CD4_rates[l][j][i]=data[NElement];
                //cout << "L: " << l << " J: " << j << " and i: " << i << endl;
                //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and Death_CD4_rates " << Death_CD4_rates[l][j][i] << endl;
            }
        }
    }
    E(cout<< "The CD4_death_rates Parameter has been loaded" << endl;)
}




void loadCD4ARTArray()
{
    E(cout<< "The CD4_ART_rates Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "CD4_ART_rates";                 // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int levels=2;
    int row=nr_rows/2;
    int col=nr_columns;
    
    
    // Lets make the *** Array
    ART_CD4_rates = new double **[levels];
    for (int i=0; i<levels; i++)
    {ART_CD4_rates[i] = new double *[row];}
    for (int i=0; i<levels; i++)
    {for (int j=0; j<row; j++)
    {ART_CD4_rates[i][j] = new double [col];}}
    
    for (int l=0; l<levels; l++){
        for (int j=0; j<row; j++){
            for (int i=0; i<col; i++){
                int NElement=i+(j*col)+(l*row*col);
                ART_CD4_rates[l][j][i]=data[NElement];
                //cout << "L: " << l << " J: " << j << " and i: " << i << endl;
                //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and ART_CD4_rates " << ART_CD4_rates[l][j][i] << endl;
            }
        }
    }
    E(cout<< "The CD4_ART_rates Parameter has been loaded" << endl;)
}



void loadNrChildren()
{
    E(cout<< "The Nr_Children Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "Nr_Children";                   // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int row=nr_rows;
    int col=nr_columns;
    
    
    // Lets make the *** Array
    NrChildrenArray = new double *[row];
    for (int i=0; i<row; i++)
    {
        NrChildrenArray[i] = new double [col];
    }
    
    for (int j=0; j<row; j++){
        for (int i=0; i<col; i++){
            int NElement=i+(j*col);
            NrChildrenArray[j][i]=data[NElement];
            //cout << "J: " << j << " and i: " << i << " NElement: " << NElement << " Data point: " << data[0] << endl;
            //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and NrChildrenArray " << NrChildrenArray[j][i] << endl;
        }
    }
    

    E(cout<< "The Nr_Children Parameter has been loaded" << endl;)
}

void loadNrChildrenProb()
{
    E(cout<< "The NrChildrenProb Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "NrChildrenProb";                      // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int col=nr_columns;
    
    
    // Lets make the *** Array
    NrChildrenProb= new double [col];
    
    for (int i=0; i<col; i++){
        NrChildrenProb[i]=data[i];
        //cout << "I: " << i << " I: " << i << endl;
        //cout << "ArrayMin " << NrChildrenProb[i] << endl;
    }
    E(cout<< "The NrChildrenProb Parameter has been loaded" << endl;)
}




void loadAgeDistribution()
{
    E(cout<< "The Age1950Array Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "Age1950Array";                  // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int row=nr_rows;
    int col=nr_columns;
    
    
    // Lets make the *** Array
    Age1950Array = new double *[row];
    for (int i=0; i<row; i++)
    {
        Age1950Array[i] = new double [col];
    }
    
    for (int j=0; j<row; j++){
        for (int i=0; i<col; i++){
            int NElement=i+(j*col);
            Age1950Array[j][i]=data[NElement];
            //cout << "J: " << j << " and i: " << i << " NElement: " << NElement << endl;
            //cout << "NElement: " << NElement << " data x: " << data[NElement] << " and Age1950Array " << Age1950Array[j][i] << endl;
        }
    }
    E(cout<< "The Age1950Array Parameter has been loaded" << endl;)
}



void loadAgeMin()
{
    E(cout<< "The ArrayMin Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "ArrayMin";                      // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int col=nr_columns;
    
    
    // Lets make the *** Array
    ArrayMin= new int [col];
    
    for (int i=0; i<col; i++){
        ArrayMin[i]=data[i];
        //cout << "I: " << i << " I: " << i << endl;
        //cout << "ArrayMin " << ArrayMin[i] << endl;
    }
    E(cout<< "The ArrayMin Parameter has been loaded" << endl;)
}



void loadAgeMax()
{
    E(cout<< "The ArrayMax Parameter is being loaded" << endl;)
    
    // 1. make a param reader object.
    CParamReader myReader;
    string fileName = ParamDirectory + "LoadParam.txt";
    if(! myReader.setNewFileName(fileName))
    {
        cout << "File " << fileName << " doesn't exist." << endl;
        exit(0);
    }
    E(cout << "File " << fileName << " successfully added.  " << endl;)
    
    
    // Some essential variables
    char ParamName[] = "ArrayMax";                      // Insert correct paramname CAREFUL: match spelling EXACTLY
    int length ;                                        // These will provide all the correct dimensions
    int nr_rows;
    int nr_columns;
    stringstream ss;                                    // These will be needed to convert from a) char* to vector and b) from vector to array
    vector<double> data;
    
    
    // Lets load the data
    char* myValue = myReader.getParamString(ParamName,length, nr_rows, nr_columns);
    //cout << endl << endl << "FINAL!!!: " << endl << ParamName << " = " << endl <<  " " << myValue << endl << "length = " << length << " nr_columns: " << nr_columns << " nr_rows: " << nr_rows << endl;
    
    
    // Lets convert to an array
    // A. First by converting char* myValue to a vector
    ss << myValue;
    double a;
    while (ss >> a){data.push_back(a);}
    
    
    // B. Second convert vector to array                // CAREFUL: This bit needs to be adapted according to if it is a 2D or 3D array!!
    int col=nr_columns;
    
    
    // Lets make the *** Array
    ArrayMax= new int [col];
    
    for (int i=0; i<col; i++){
        ArrayMax[i]=data[i];
        //cout << "I: " << i << " I: " << i << endl;
        //cout << "ArrayMax " << ArrayMax[i] << endl;
    }
    E(cout<< "The ArrayMax Parameter has been loaded" << endl;)
}






///////////////////////////////////////
/////// --- LOAD KEY ARRAYS --- ///////
///////////////////////////////////////




/////////////////////
// -- NCD Array -- //
/////////////////////

void loadNCDArray(){
    
    E(cout << "Lets load the NCD array. " << endl;)
    ifstream myfile(ParamDirectory + "NCDArray.csv");
    
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file NCDArray was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file NCDArray was bad!" << endl;
        exit(0);
    }
    
    // Else lets load the Array
    cout << "File " << &myfile << " successfully added" << endl;
    NCDArray = new double *[nr_NCDs];
    for (int row = 0; row<nr_NCDs; row++){				// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);
        
        
        NCDArray[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  NCDArray[row][col];
        }
    }
   
    
    
    E(cout << "NCDArray array has been read in successfully! " << endl;)
}



////////////////////////
// -- Cancer Array -- //
////////////////////////

void loadCancerArray(){
    
    E(cout << "Lets load the Cancer array. " << endl;)
    ifstream myfile(ParamDirectory + "CancerArray.csv");
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file CancerArray was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file CancerArray was bad!" << endl;
        exit(0);
    }
    
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    CancerArray = new double *[7];
    for (int row = 0; row<7; row++){				// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);
        
        
        CancerArray[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  CancerArray[row][col];
            //cout << "testing " << CancerArray[row][col] << " col " << col << " row  " << row << endl;
        }
    }
    
    
    E(cout << "CancerArray array has been read in successfully! " << endl;)
}



///////////////////////////
// -- Fertility Array -- //
///////////////////////////

void loadBirthArray(){
    
    E(cout << "Lets load the fertility array. " << endl;)
    ifstream myfile(ParamDirectory + "fertility.csv");
    

    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file Fertility was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file Fertility was bad!" << endl;
        exit(0);
    }
   
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    BirthArray = new double *[301];
    for (int row = 0; row<301; row++){				// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);

        
        BirthArray[row]=new double[35];
        for (int col = 0; col<35; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  BirthArray[row][col];
        }
    }
    
    
    E(cout << "Fertility array has been read in successfully! " << endl;)
}


/////////////////////////////////////
// -- Mortality Array for women -- //
/////////////////////////////////////

void loadDeathArray_Women(){
    
    E(cout << "Lets load the death array for women. " << endl;)
    ifstream myfile(ParamDirectory + "mortality_array_women.csv");
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file Mortality Array Women was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file Mortality Array Women was bad!" << endl;
        exit(0);
    }
    
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    DeathArray_Women = new double *[301];
    for (int row = 0; row<301; row++){				// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);
        
        DeathArray_Women[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  DeathArray_Women[row][col];
        }
    }
    E(cout << "Mortality array for women has been read in successfully! " << endl;)
}

    
    
///////////////////////////////////
// -- Mortality Array for men -- //
///////////////////////////////////

void loadDeathArray_Men()
{
    E(cout << "Lets load the death array for men. " << endl;)
    ifstream myfile(ParamDirectory + "mortality_array_men.csv");
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file Mortality Array Men was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file Mortality Array Men was bad!" << endl;
        exit(0);
    }
    
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    DeathArray_Men = new double *[301];
        for (int row = 0; row<301; row++){				// This loop will read in every number to the right place
            string line;
            getline(myfile, line);
            stringstream iss(line);
        
        DeathArray_Men[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  DeathArray_Men[row][col];
        }
    }
    E(cout << "Mortality array for men has been read in successfully! " << endl;)
}

    

///////////////////////////////
// -- HIV Incidence Women -- //
///////////////////////////////

void loadHIVArray_Women()
{
    
    E(cout << "Lets load the HIV array for women.  " << endl;)
    ifstream myfile(ParamDirectory + "HIV_incidence_women.csv");
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file Incidence Array Women was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file Incidence Array Women was bad!" << endl;
        exit(0);
    }
   
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    HIVArray_Women = new double *[201];
    for (int row = 0; row<201; row++){					// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);
        
        HIVArray_Women[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  HIVArray_Women[row][col];
        }
    }
    E(cout << "HIV array for women has been read in successfully! " << endl;)
}



/////////////////////////////
// -- HIV Incidence Men -- //
/////////////////////////////

void loadHIVArray_Men(){
    
    E(cout << "Lets load the HIV array for men.  " << endl;)
    ifstream myfile(ParamDirectory + "HIV_incidence_men.csv");
    
    // Lets include an error message in case file is not found
    if (!myfile.is_open())
    {
        cout << "ERROR: The file Incidence Array Men was not found!" << endl;
        exit(0);
    }
    else if (myfile.bad())
    {
        cout << "ERROR: The file Incidence Array Men was bad!" << endl;
        exit(0);
    }
    
    // Else lets load the Array
    E(cout << "File " << &myfile << " successfully added" << endl;)
    HIVArray_Men = new double *[201];
    for (int row = 0; row<201; row++){					// This loop will read in every number to the right place
        string line;
        getline(myfile, line);
        stringstream iss(line);
        
        HIVArray_Men[row]=new double[121];
        for (int col = 0; col<121; col++){
            string val;
            getline (iss, val, ',');
            stringstream convertor(val);
            convertor >>  HIVArray_Men[row][col];
        }
    }
    E(cout << "HIV array for men has been read in successfully! " << endl;)
}
