//
//  KruskalEdge.h
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef KRUSKAL_EDGE_H_
#define KRUSKAL_EDGE_H_

#include <platform.h>

class RandomI;

enum KruskalEdgeType
{
    KRUSKAL_EDGE_TYPE_UNDEFINED = 0,
    KRUSKAL_EDGE_TYPE_VWALL = 1,
    KRUSKAL_EDGE_TYPE_HWALL = 2
};

struct KruskalEdge {
public:
    KruskalEdge();
    ~KruskalEdge();
    
    KruskalEdgeType type;
    int x;
    int z;
    
    static void Shuffle(Array<KruskalEdge>& edges, RandomI* shuffler, int nShuffles);
};

#endif
