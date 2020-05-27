//
//  MazeBVHNode.h
//  Dissert
//
//  Created by Olivier Legat on 22/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MAZE_BVH_NODE_H_
#define MAZE_BVH_NODE_H_

#include <platform.h>

#include "MazeCollider.h"

class MazeBVHNode : public Object
{
    friend class MazeBVH;
    
protected:
    MazeBVHNode(MazeBVHNode** children, float childrenCount);
    MazeBVHNode(MazeCollider* collider);
    MazeBVHNode();
    
    /**
     * Delete this node and its collider. Recursively calls ~MazeBVNode()
     * on all its children. Also set parent to NULL.
     */
    ~MazeBVHNode();
    
public:
    int GetChildrenCount() const { return (int) children.size(); }
    MazeBVHNode* GetChild(int index) const { return children[index]; }
    MazeBVHNode* GetParent() const { return parent; }
    MazeCollider* GetCollider() const { return collider; }
    
    bool IsLeaf() const { return GetChildrenCount() == 0; }
    bool IsRoot() const { return parent == NULL; }
    int  GetHeight() const { return height; }
    
private:
    int height;
    MazeCollider* collider;
    MazeBVHNode* parent;
    Array<MazeBVHNode*> children;
};

#endif
