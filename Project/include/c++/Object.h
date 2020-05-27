//
//  Object.h
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>

class Object
{
public:
    Object();
    ~Object();
    
    virtual std::string ToString() const;
};

#endif
