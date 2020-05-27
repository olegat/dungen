//
//  File.h
//  Dissert
//
//  Created by Olivier Legat on 15/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MY_FILE_H_
#define MY_FILE_H_

#include <platform.h>

class File
extends Object
{
public:
    File();
    File(String filename);
    ~File();
    
    const String GetFullname() const;
    void SetFilename(String filename);
    
    static void SetWorkingDirectory(String s);
    static void InitFilesystem();
    
private:
    String filename;
    static String pwd;
    
    static String ditchQuotes(String s);
};

#endif
