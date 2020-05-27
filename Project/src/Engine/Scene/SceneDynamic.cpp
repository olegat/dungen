//
//  SceneDynamic.cpp
//  Dissert
//
//  Created by Olivier Legat on 24/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "SceneDynamic.h"

SceneDynamic::SceneDynamic(MazeColliderAABB* aabb)
{
    this->aabb = aabb;
    this->visible = true;
}
SceneDynamic::~SceneDynamic()
{
    delete aabb;
}

void SceneDynamic::Translate(Vector3 t)
{
    Vector3 x = this->aabb->GetTranslation();
    this->aabb->SetTranslation(x + t);
}
