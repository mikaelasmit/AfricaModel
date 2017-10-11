/////////////////////////////////////////////////////////////////
//    CParamReader.cpp                                         //
//    Created by Mikaela Smit on 29/10/2015.				   //
//    Copyright (c) 2015 Mikaela Smit. All rights reserved.    //
//    Makes arrays from parameters being uploaded              //
/////////////////////////////////////////////////////////////////


#include <iostream>                   
#include <string.h>
#include <vector>
#include <string>
#include "CParamReader.hpp"
#include "errorcoutmacro.h"

using namespace std;


// Class Constructor
CParamReader::CParamReader()
{
    paramBuffer = new char[BUFFER_SIZE];
    filePathString = NULL;
}

// Class Destructor
CParamReader::~CParamReader()
{
    delete[] paramBuffer;
    if(filePathString!=NULL)
        delete[] filePathString;
}


// Set the file name and check that it exists, unattaches previous file if necessary.

bool CParamReader::setNewFileName(string filePath)

{
    
    if(paramFileStream.is_open())       // If there's a file attached, remove it.
        paramFileStream.close();
    
    paramFileStream.open(filePath);
    
    if(!paramFileStream.is_open())
        return false;
    
    paramFileStream.close();            // Just checking, close it
    
    filePathString = new char[filePath.length()+1];
    strcpy(filePathString, filePath.c_str());

    
    return true;
}

// Return a string containing parameter data or NULL and also the length of the vector.
char* CParamReader::getParamString(const char* paramName, int& nElements, int& rows, int& columns)
{
    // Do we have a file attached?
    paramFileStream.open(filePathString);
    
    if(!paramFileStream.is_open())
        return NULL;
    
    // Declare variables needed
    bool found = false;
    string paramString;
    string paramContainer;
    char* token;
    int nullTerminal;
    
    //int countrounds=0;
    
    // Run through the lines of the file for the parameter
    while(!paramFileStream.eof() && !found)
    {
        paramFileStream.getline(paramBuffer,BUFFER_SIZE-1);     // this updates 'token'
        token = strtok(paramBuffer,"\t");                       // This reads the first bit until 'new line' "\n" - i.e. the variable name for the new variable
    
        // Anything on this line?
        if(token!=NULL)
        {
            // Line doesn't begin with # or ; and matches param name?
            if(token[0]!='#'&& token[0]!=';' && strcmp(paramName,token)==0)
            {
                columns=0;                                      // Initialise the rows and columns back to 0
                rows=0;
                //cout << "The following is being loaded " << token << endl;
                
                while (token[0]!=';')
                {
                    // 1. Lets get the next line and first line of data
                    paramFileStream.getline(paramBuffer,BUFFER_SIZE-1);         // this updates 'token'
                    //cout << "Token: " << token << endl;
                    
                    // We will run this until we find the ; - which annotes end of the variable data
                    if (token[0]!=';' && token[0]!=' ' && token!=NULL && token[0]!='#')
                    {
                        // 2. Remove any extra spaces from the end of the string (as long as the string isn't zero lnegth).
                        nullTerminal = strlen(token);		// This gets the length of the char string
                        while(token[nullTerminal-1]==' '||token[nullTerminal-1]=='\t')                       // This finds the extra spaces at the end and deletes them
                        {nullTerminal--;}
                        token[nullTerminal] = '\0';                             // ends the string in a specific way
                        paramString = strtok(token,"\n");                       // copy the clean data (w/o spaces) to temporary 'holding' container
                        //cout << paramString << endl;
                        
                        // 3. Lets add the data to the paramContainer
                        if (rows==0)
                        {
                            paramContainer=paramString;             // Copy the final 'long' holding container
                            
                            // 4. Lets count the number of elements in this line to ger nr_columns
                            nullTerminal=paramContainer.length();
                            for(int c=0; c<nullTerminal; c++)
                            {if (paramContainer[c]=='\t'){columns++;}}
                            columns=columns+1;                      // As we removed spaces at the end we need to add 1
                            //cout << "Columns check: " << columns << endl;
                        }
                        
                        // 5. Add the next line to the holding container
                        else if (rows>0)
                        {
                            paramContainer.append(" ");             // First we need to add a space at the end - otherwise it will stick 2 nurmber together
                            paramContainer.append(paramString);     // Now we add the new line to the end of the long holding container
                        }
                        
                        
                        // 6. Lets count the number of rows
                        rows++;
                        
                        //cout << "Round 2: " << endl;
                        //cout << "ParamStr: \t" << paramString << endl;
                        //cout << "Container: \t" << paramContainer << endl;
                    }
                }
                found = true;
                paramContainer=paramContainer;
                //cout << "FINAL: " <<paramContainer << " rows: " << rows << " columns: " << columns << endl;
            }
        }
        //countrounds++;
        //cout << "Counts is: " << countrounds << " and token: " << token << endl;
    }
    
    
    // 7. Make the final variable a char*
    char* charContainer = new char[paramContainer.length() +1];     // Convert the container to a char*
    strcpy(charContainer, paramContainer.c_str());                  // Assign the correct variables
    
    // 8. Count the total nr of elements in the variables count the spaces
    nullTerminal = strlen(charContainer);		// This gets the length of the char string
    int count = 0;
    for(int j=0;j<nullTerminal;j++)
    {if(paramContainer[j]=='\t') {count++;}}
    nElements=count + (1*rows);
    //cout << "NElement check: " << nElements << endl;
    
    paramFileStream.close();
    
    return charContainer;
}



