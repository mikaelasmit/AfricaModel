/////////////////////////////////////////////////////////////////
//    CParamReader.hpp                                         //
//    Created by Mikaela Smit on 29/10/2015.				   //
//    Copyright (c) 2015 Mikaela Smit. All rights reserved.    //
//    Makes arrays from parameters being uploaded              //
/////////////////////////////////////////////////////////////////


#ifndef CPARAMREADER_H_
#define CPARAMREADER_H_

#include <fstream>

#define BUFFER_SIZE 1024		// Define Buffer-size - dwefine piece of memory where it can stick things

class CParamReader
{
public:
    CParamReader();
    virtual ~CParamReader();	// destructor
    
    bool setNewFileName(char* filePath);                                                        // return true or false
    char* getParamString(const char* paraName, int& nElements, int& rows, int& columns);        // This will output name, size, nr_rows, nr_col for the parameter from the text file
    
    
    // Members...
    std::ifstream paramFileStream;
    char* paramBuffer;
    char* filePathString;
};

#endif /* CPARAMREADER_H_ */

