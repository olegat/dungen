//
//  MazeBVHNode.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "MazeBVHNode.h"
#include "MazeCollider.h"

MazeBVHNode::MazeBVHNode(MazeBVHNode** children, float childrenCount)
{
    MazeColliderAABB* myCollider = new MazeColliderAABB();
    this->height = 0;
    
    if(childrenCount > 0)
    {
        float x, y, z, X, Y, Z; // min/max x,y,z values.
        
        // Init collider (use AABB of 1st child)
        children[0]->GetCollider()->GetAllMinMax(&x, &y, &z, &X, &Y, &Z);
        
        // For each child (other than the first)
        for (int i = 1; i < childrenCount; i ++ )
        {
            // Get children with max height.
            if (children[i]->height > this->height)
                this->height = children[i]->height;
            
            float a;
            MazeCollider* c = children[i]->GetCollider();
            
            // Calc min:
            if( (a = c->GetMinX()) < x ) x = a;
            if( (a = c->GetMinY()) < y ) y = a;
            if( (a = c->GetMinZ()) < z ) z = a;
            
            // Calc max:
            if( (a = c->GetMaxX()) > X ) X = a;
            if( (a = c->GetMaxY()) > Y ) Y = a;
            if( (a = c->GetMaxZ()) > Z ) Z = a;
        }
        
        // Set translation and volume:
        myCollider->SetX(x/2 + X/2);
        myCollider->SetY(y/2 + Y/2);
        myCollider->SetZ(z/2 + Z/2);
        myCollider->SetWidth (X - x);
        myCollider->SetLength(Z - z);
        myCollider->SetHeight(Y - y);
        
        // Add children:
        this->children = Array<MazeBVHNode*>(childrenCount, NULL);
        for (int j = 0; j < childrenCount; j++)
        {
            this->children[j] = children[j];
            this->children[j]->parent = this;
        }
    }
    
    this->height = height + 1;
    this->collider = myCollider;
}

MazeBVHNode::MazeBVHNode(MazeCollider* collider)
{
    this->collider = collider;
    this->parent = NULL;
    this->height = 0;
}

MazeBVHNode::MazeBVHNode()
{
    this->collider = NULL;
    this->parent   = NULL;
    this->height   = 0;
    this->children = Array<MazeBVHNode*>();
}
MazeBVHNode::~MazeBVHNode()
{
    if(collider!=NULL) delete collider;
    
    for (int i = 0; i < this->children.size(); i++)
        delete children[i];
    
    parent = NULL;
    children.clear();
}
