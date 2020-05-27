//
//  KruskalEdge.cpp
//  Dissert
//
//  Created by Olivier Legat on 22/06/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "KruskalEdge.h"
#include <Generator/Random/Random.h>

KruskalEdge::KruskalEdge()
{
    type = KRUSKAL_EDGE_TYPE_UNDEFINED;
    x = 0;
    z = 0;
}

KruskalEdge::~KruskalEdge()
{
    
}

void KruskalEdge::Shuffle(Array<KruskalEdge>& edges, RandomI* shuffler, int nShuffles)
{
    int i;
    int j;
    int n = (int) edges.size();
    
    for ( int m = 0; m < nShuffles; m++)
    {
        for ( i = 0 ; i < n; i++ )
        {
            j = i;
            while (j == i) j = shuffler->nextInt(0, n);
            
            KruskalEdge swap = edges[i];
            edges[i] = edges[j];
            edges[j] = swap;
        }
    }
}
