//
//  ArgParser.h
//  Dissert
//
//  Created by Olivier Legat on 25/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef ARG_PARSER_H_
#define ARG_PARSER_H_

#include <platform.h>

namespace ArgParser 
{
    /**
     * Get the index of the option
     * @param option     Full-name of the option. e.g. --working-directory
     * @param alias      The short-name of the option. e.g. -w
     * @param argc,argv  Same as in main(int,char**).
     * @return Index of the option. -1 if the option is not found.
     */
    int getArgIndex(const char* option, const char* alias, int argc, const char ** argv);
    
    /**
     * @param index      Index of the option name
     * @param argc,argv  Same as in main(int,char**).
     * @return true if argv[index] has a value assigned.
     */
    bool hasValue(int index, int argc, const char ** argv);
}

#endif
