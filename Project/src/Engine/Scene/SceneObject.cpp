//
//  SceneObject.cpp
//  Dissert
//
//  Created by Olivier Legat on 07/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "SceneObject.h"

SceneObject::SceneObject(unsigned int Id, String name) {
    this->Id = Id;
    this->name = name;
    this->mesh = NULL;
    this->bvh  = NULL;
    this->rendermesh = true;
    this->renderbvh  = false;
}
SceneObject::~SceneObject() {
    
}
