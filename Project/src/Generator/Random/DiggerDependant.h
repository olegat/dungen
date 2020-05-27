//
//  DiggerDependant.h
//  Dissert
//
//  Created by Olivier Legat on 29/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef DIGGER_DEPENDANT_H_
#define DIGGER_DEPENDANT_H_

#include <platform.h>

class Digger;

interface DiggerDependant
{
private:
    Digger* digger;
    
protected:
    DiggerDependant();
    
public:
    ~DiggerDependant();
    
    void SetDigger(Digger* digger) {this->digger = digger;}
    Digger* GetDigger() const {return this->digger;}
};

#endif
