//
//  Math.cpp
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Math.h"

namespace Math 
{
    
    template <class T> T max(T x, T y)
    {
        return x > y ? x : y ;
    }
    template <> int max<int>(int x, int y)
    {
        return x > y ? x : y ;
    }
    template <class T> T min(T x, T y)
    {
        return x < y ? x : y ;
    }
    
    template <> Vector3 max<Vector3>(Vector3 a, Vector3 b)
    {
        Vector3 c = Vector3(0);
        c.x = Math::max(a.x, b.x);
        c.y = Math::max(a.y, b.y);
        c.z = Math::max(a.z, b.z);
        return c;
    }
    template <> Vector3 min<Vector3>(Vector3 a, Vector3 b)
    {
        Vector3 c = Vector3(0);
        c.x = Math::min(a.x, b.x);
        c.y = Math::min(a.y, b.y);
        c.z = Math::min(a.z, b.z);
        return c;
    }
    
    template <class T> T sign(T x)
    {
        return x < 0 ? (T)-1 : (T)1;
    }
    
    template <> float sign<float>(float x)
    {
        return x < 0 ? -1.0f : 1.0f;
    }
}
