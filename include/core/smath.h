#pragma once

#include "defines.h"

typedef struct SGvec2 {
    float x, y;
} SGvec2;

typedef struct SGvec3 {
    float x, y, z;
} SGvec3;

typedef struct SGvec4 {
    float x, y, z, w;
} SGvec4;

// SGmat4, 4x4 components, column major, OpenGL style, right handed
typedef struct SGmat4 {
    float m0, m4, m8, m12;      // SGmat4 first row (4 components)
    float m1, m5, m9, m13;      // SGmat4 second row (4 components)
    float m2, m6, m10, m14;     // SGmat4 third row (4 components)
    float m3, m7, m11, m15;     // SGmat4 fourth row (4 components)
} SGmat4;

