//
//  Parser.h
//  Dissert
//
//  Created by Olivier Legat on 28/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_PROFILE_PARSER_H_
#define MAZE_PROFILE_PARSER_H_

#include <platform.h>

class RandomI;
class RandomF;
class Digger;
class Maze;

class ProfileParser
extends Object
{
public:
    /**
     * Parse the profile from a filename.
     * @param filename a file
     * @param seed UniformRandom seed.
     * @param maze An initialized maze.
     * @return true if syntaxly correct. false if an error occurs.
     */
    static bool ParseProfile(String filename, long seed, Maze* maze);
    
    /**
     * Removes spaces and tabs from a string.
     * @param str any string.
     * @return str without spaces or tabs.
     */
    static String RemoveWhiteChars(String str);
    
    /**
     * Get get value of a field.
     * @param wholeString A line in the file (no spaces nor tabs).
     * @param keyWord name of the field.
     * @param value [output] points to a string representing the value.
     * @return true if wholeString contains keyWords and is syntaxically correct.
     *         false otherwise.
     */
    static bool GetValue(String wholeString, String keyWord, String* value);
    
    static Array<Object*> RandomArray;
    static Array<Digger*> DiggerArray;
    
    /**
     * Clear RandomArray, DiggerArray and delete the Random number generators and diggers.
     */
    static void ClearArrays();
};

#endif
