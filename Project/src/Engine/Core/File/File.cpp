//
//  File.cpp
//  Dissert
//
//  Created by Olivier Legat on 15/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "File.h"

#ifdef WINDOWS
    #include <direct.h>
    #define getWorkingDir _getcwd
#else
    #include <unistd.h>
    #define getWorkingDir getcwd
#endif

String File::pwd = "";

File::File()
{
    filename = "";
}

File::File(String filename)
{
    SetFilename(filename);
}

File::~File()
{
    
}

const String File::GetFullname() const
{
    return this->filename;
}

void File::SetFilename(String filename)
{
    filename = ditchQuotes(filename);

    if (filename[0] == '/')
		this->filename = filename;

    else this->filename = pwd + "/" + filename;
}

void File::SetWorkingDirectory(String s)
{
    s = ditchQuotes(s);
    
    pwd.clear();
    pwd = s;
}

void File::InitFilesystem()
{
    char path [FILENAME_MAX];
    
    char* c = getWorkingDir(path, sizeof(path) / sizeof(char) );
    assert ( c );
    
    pwd.clear();
    pwd = String(path);
}

String File::ditchQuotes(String s)
{
    if(s[0]=='\"' && s[s.length()-1] == '\"')
        return s.substr(1, s.length()-2);
    else return s;
}
