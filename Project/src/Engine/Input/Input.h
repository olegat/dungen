//
//  Input.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef INPUT_H_
#define INPUT_H_

#include <platform.h>
#include "Keyboard.h"
#include "Mouse.h"

class Input
extends Object
{
public:
    static void Init();
    static void Destroy();
    
    static void Update() {Keyboard::Update(); Mouse::Update();}
    
private:
    static void remapInputHandlers();
};

#endif
