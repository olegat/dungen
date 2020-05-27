//
//  ArgParser.cpp
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "ArgParser.h"

namespace ArgParser
{
    int getArgIndex(const char* option, const char* alias, int argc, const char ** argv)
    {
        assert(option); assert(argv);
        
        for (int i = 0; i < argc; i++)
        {
            if ( strcmp(option, argv[i]) == 0) {return i;}
            if ( alias!=NULL && strcmp(alias, argv[i]) == 0) {return i;}
        }
        
        return -1;
    }
    
    bool hasValue(int index, int argc, const char ** argv)
    {
        // Index is out of range"
        if ( index < 0 ) return false;
        
        // Index is last arg (or out of range):
        if ( index >= argc - 1 ) return false; 
        
        // The string after argv[index] is a value is it doesn't
        // begin with a dash
        else return argv[index+1][0] != '-';
    }
}
