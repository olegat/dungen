//
//  Math.h
//  Dissert
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#ifndef MY_MATH_H_
#define MY_MATH_H_

#include <platform.h>

#ifndef roundf
#define roundf(x) (int) (x + 0.5f)
#endif

namespace Math 
{
#define PI 3.14159265358979323846
#define PI_OVER_180	 0.017453292519943295769236907684886
#define PI_OVER_360	 0.0087266462599716478846184538424431
#define DEG2RAD(x) ((x) * ((PI) / (180.0f)))
#define RAD2DEG(x) ((x) * ((180.0f) / (PI)))
    
    template <class T> T max(T x, T y);
    template <class T> T min(T x, T y);
    
    /**
     * @return A vector where x = max(a.x, b.x),  y = max(a.y, b.y),  z = max(a.z, b.z);
     */
    template <> Vector3 max<Vector3>(Vector3 a, Vector3 b);
    
    /**
     * @return A vector where x = min(a.x, b.x),  y = min(a.y, b.y),  z = min(a.z, b.z);
     */
    template <> Vector3 min<Vector3>(Vector3 a, Vector3 b);
    
    /**
     * @returns -1 if x<0 or 1 if x>=0
     */
    template <class T> T sign(T x);
}

#endif
