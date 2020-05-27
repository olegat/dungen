//
//  PathLogger.h
//  Dissert
//
//  Created by Olivier Legat on 27/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef PATH_LOGGER_H_
#define PATH_LOGGER_H_

#include <platform.h>

interface PathLogger
{
protected:
    PathLogger()  {log = false;}
    
public:
    ~PathLogger() {}
    
    void SetLoggingPath(bool l) {log = l;}
    bool isLoggingPath()        {return log;}
    
private:
    bool log;
};

#endif
