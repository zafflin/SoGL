#pragma once

#include <math.h>
#include "defines.h"

#define SG_PI		3.14159265358979323846      // M_PI equivalent

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
    float m0, m4, m8, m12;
    float m1, m5, m9, m13;
    float m2, m6, m10, m14;
    float m3, m7, m11, m15;
} SGmat4;


// VEC2
void sgGetVec2Str(const SGvec2* vec) {
    printf("SGvec2 {\n");
    printf("  x: %.2f,\n", vec->x);
    printf("  y: %.2f,\n", vec->y);
    printf("}\n");
}

void sgScalarVec2a(SGvec2* v1, u32 scalar) {
    v1->x+=scalar;
    v1->y+=scalar;
}

void sgScalarVec2s(SGvec2* v1, u32 scalar) {
    v1->x-=scalar;
    v1->y-=scalar;
}

void sgNegVec2(SGvec2* v1) {
    v1->x=-v1->x;
    v1->y=-v1->y;
}

void sgAddVec2(SGvec2* v1, SGvec2 v2) {
    v1->x+=v2.x;
    v1->y+=v2.y;
}

void sgSubVec2(SGvec2* v1, SGvec2 v2) {
    v1->x+=(-v2.x);
    v1->y+=(-v2.y);
}

f32 sgLenVec2(SGvec2 vec) {
    f32 v1 = sqrtf( ( ( vec.x * vec.x ) + ( vec.y * vec.y )) );
    return v1;
}

void sgNormVec2(SGvec2* v1) {
    f32 len = sgLenVec2(*v1);
    v1->x /= len;
    v1->y /= len;
}

f32 sgDotVec2(SGvec2 v1, SGvec2 v2) {
    return ( (v1.x * v2.x) + (v1.y * v2.y) );
}

f32 sgCrossVec2(const SGvec2* v1, const SGvec2* v2) {
    return (v1->x * v2->y) - (v1->y * v2->x);
}


// VEC3
void sgGetVec3Str(const SGvec3* vec) {
    printf("SGvec3 {\n");
    printf("  x: %.2f,\n", vec->x);
    printf("  y: %.2f,\n", vec->y);
    printf("  z: %.2f\n", vec->z);
    printf("}\n");
}

void sgScalarVec3a(SGvec3* v1, u32 scalar) {
    v1->x+=scalar;
    v1->y+=scalar;
    v1->z+=scalar;
}

void sgScalarVec3s(SGvec3* v1, u32 scalar) {
    v1->x-=scalar;
    v1->y-=scalar;
    v1->z-=scalar;
}

void sgNegVec3(SGvec3* v1) {
    v1->x=-v1->x;
    v1->y=-v1->y;
    v1->z=-v1->z;
}

void sgAddVec3(SGvec3* v1, SGvec3 v2) {
    v1->x+=v2.x;
    v1->y+=v2.y;
    v1->z+=v2.z;
}

void sgSubVec3(SGvec3* v1, SGvec3 v2) {
    v1->x+=(-v2.x);
    v1->y+=(-v2.y);
    v1->z+=(-v2.z);
}

f32 sgLenVec3(SGvec3 vec) {
    f32 v1 = sqrtf( ( ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) ) );
    return v1;
}

void sgNormVec3(SGvec3* v1) {
    f32 len = sgLenVec3(*v1);
    v1->x /= len;
    v1->y /= len;
    v1->z /= len;
}

f32 sgDotVec3(SGvec3 v1, SGvec3 v2) {
    return ( (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) );
}

void sgCrossVec3(SGvec3* v1, SGvec3 v2) {
    float temp_x = v1->x;
    float temp_y = v1->y;
    float temp_z = v1->z;

    v1->x = (temp_y * v2.z) - (temp_z * v2.y);
    v1->y = (temp_z * v2.x) - (temp_x * v2.z);
    v1->z = (temp_x * v2.y) - (temp_y * v2.x);
}


// VEC4
void sgGetVec4Str(const SGvec4* vec) {
    printf("SGvec3 {\n");
    printf("  x: %.2f,\n", vec->x);
    printf("  y: %.2f,\n", vec->y);
    printf("  z: %.2f\n", vec->z);
    printf("  w: %.2f\n", vec->w);
    printf("}\n");
}

void sgScalarVec4a(SGvec4* v1, u32 scalar) {
    v1->x+=scalar;
    v1->y+=scalar;
    v1->z+=scalar;
    v1->w+=scalar;
}

void sgScalarVec4s(SGvec4* v1, u32 scalar) {
    v1->x-=scalar;
    v1->y-=scalar;
    v1->z-=scalar;
    v1->w-=scalar;
}

void sgNegVec4(SGvec4* v1) {
    v1->x=-v1->x;
    v1->y=-v1->y;
    v1->z=-v1->z;
    v1->w=-v1->w;
}

void sgAddVec4(SGvec4* v1, SGvec4 v2) {
    v1->x+=v2.x;
    v1->y+=v2.y;
    v1->z+=v2.z;
    v1->w+=v2.w;
}

void sgSubVec4(SGvec4* v1, SGvec4 v2) {
    v1->x+=(-v2.x);
    v1->y+=(-v2.y);
    v1->z+=(-v2.z);
    v1->w+=(-v2.w);
}

f32 sgLenVec4(SGvec4 vec) {
    f32 v1 = sqrtf( ( ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) + ( vec.w * vec.w ) ) );
    return v1;
}

void sgNormVec4(SGvec4* v1) {
    f32 len = sgLenVec4(*v1);
    v1->x /= len;
    v1->y /= len;
    v1->z /= len;
    v1->w /= len;
}

f32 sgDotVec4(SGvec4 v1, SGvec4 v2) {
    return ( (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z) + (v1.w * v2.w) );
}


// MAT4
void sgGetMat4Str(const SGmat4* mat) {
    printf("SGmat4 {\n");
    printf("  %.2f %.2f %.2f %.2f\n", mat->m0, mat->m4, mat->m8, mat->m12);
    printf("  %.2f %.2f %.2f %.2f\n", mat->m1, mat->m5, mat->m9, mat->m13);
    printf("  %.2f %.2f %.2f %.2f\n", mat->m2, mat->m6, mat->m10, mat->m14);
    printf("  %.2f %.2f %.2f %.2f\n", mat->m3, mat->m7, mat->m11, mat->m15);
    printf("}\n");
}

SGmat4 sgIdentity(void) {
    return (SGmat4) {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };
}

void sgScalarMat4(SGmat4* m1, u32 scalar) {
    m1->m0*=scalar;  m1->m4*=scalar;  m1->m8*=scalar;  m1->m12*=scalar;
    m1->m1*=scalar;  m1->m5*=scalar;  m1->m9*=scalar;  m1->m13*=scalar;
    m1->m2*=scalar;  m1->m5*=scalar;  m1->m10*=scalar;  m1->m14*=scalar;
    m1->m3*=scalar;  m1->m7*=scalar;  m1->m11*=scalar;  m1->m15*=scalar;
}

void sgAddMat4(SGmat4* m1, SGmat4 m2) {
    m1->m0 += m2.m0; m1->m4 += m2.m4; m1->m8 += m2.m8; m1->m12 += m2.m12;
    m1->m1 += m2.m1; m1->m5 += m2.m5; m1->m9 += m2.m9; m1->m13 += m2.m13;
    m1->m2 += m2.m2; m1->m6 += m2.m6; m1->m10 += m2.m10; m1->m14 += m2.m14;
    m1->m3 += m2.m3; m1->m7 += m2.m7; m1->m11 += m2.m11; m1->m15 += m2.m15;
}

void sgSubMat4(SGmat4* m1, SGmat4 m2) {
    m1->m0 -= m2.m0; m1->m4 -= m2.m4; m1->m8 -= m2.m8; m1->m12 -= m2.m12;
    m1->m1 -= m2.m1; m1->m5 -= m2.m5; m1->m9 -= m2.m9; m1->m13 -= m2.m13;
    m1->m2 -= m2.m2; m1->m6 -= m2.m6; m1->m10 -= m2.m10; m1->m14 -= m2.m14;
    m1->m3 -= m2.m3; m1->m7 -= m2.m7; m1->m11 -= m2.m11; m1->m15 -= m2.m15;
}

void sgMulMat4(SGmat4* result, SGmat4 m1, SGmat4 m2) {
    result->m0 = m1.m0 * m2.m0 + m1.m4 * m2.m1 + m1.m8 * m2.m2 + m1.m12 * m2.m3;
    result->m4 = m1.m0 * m2.m4 + m1.m4 * m2.m5 + m1.m8 * m2.m6 + m1.m12 * m2.m7;
    result->m8 = m1.m0 * m2.m8 + m1.m4 * m2.m9 + m1.m8 * m2.m10 + m1.m12 * m2.m11;
    result->m12 = m1.m0 * m2.m12 + m1.m4 * m2.m13 + m1.m8 * m2.m14 + m1.m12 * m2.m15;

    result->m1 = m1.m1 * m2.m0 + m1.m5 * m2.m1 + m1.m9 * m2.m2 + m1.m13 * m2.m3;
    result->m5 = m1.m1 * m2.m4 + m1.m5 * m2.m5 + m1.m9 * m2.m6 + m1.m13 * m2.m7;
    result->m9 = m1.m1 * m2.m8 + m1.m5 * m2.m9 + m1.m9 * m2.m10 + m1.m13 * m2.m11;
    result->m13 = m1.m1 * m2.m12 + m1.m5 * m2.m13 + m1.m9 * m2.m14 + m1.m13 * m2.m15;

    result->m2 = m1.m2 * m2.m0 + m1.m6 * m2.m1 + m1.m10 * m2.m2 + m1.m14 * m2.m3;
    result->m6 = m1.m2 * m2.m4 + m1.m6 * m2.m5 + m1.m10 * m2.m6 + m1.m14 * m2.m7;
    result->m10 = m1.m2 * m2.m8 + m1.m6 * m2.m9 + m1.m10 * m2.m10 + m1.m14 * m2.m11;
    result->m14 = m1.m2 * m2.m12 + m1.m6 * m2.m13 + m1.m10 * m2.m14 + m1.m14 * m2.m15;

    result->m3 = m1.m3 * m2.m0 + m1.m7 * m2.m1 + m1.m11 * m2.m2 + m1.m15 * m2.m3;
    result->m7 = m1.m3 * m2.m4 + m1.m7 * m2.m5 + m1.m11 * m2.m6 + m1.m15 * m2.m7;
    result->m11 = m1.m3 * m2.m8 + m1.m7 * m2.m9 + m1.m11 * m2.m10 + m1.m15 * m2.m11;
    result->m15 = m1.m3 * m2.m12 + m1.m7 * m2.m13 + m1.m11 * m2.m14 + m1.m15 * m2.m15;
}

void sgScaleMat4(SGmat4* m1, SGvec3 vec) {
    m1->m0 *= vec.x;
    m1->m5 *= vec.y;
    m1->m10 *= vec.z;
}

void sgTransMat4(SGmat4* m1, SGvec3 vec) {
    m1->m12 += vec.x;
    m1->m13 += vec.y;
    m1->m14 += vec.z;
}

void sgRotXMat4(SGmat4* m1, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    
    m1->m0 = 1.0f; m1->m4 = 0.0f;     m1->m8 = 0.0f;     m1->m12 = 0.0f;
    m1->m1 = 0.0f; m1->m5 = cosTheta; m1->m9 = -sinTheta; m1->m13 = 0.0f;
    m1->m2 = 0.0f; m1->m6 = sinTheta; m1->m10 = cosTheta; m1->m14 = 0.0f;
    m1->m3 = 0.0f; m1->m7 = 0.0f;     m1->m11 = 0.0f;     m1->m15 = 1.0f;
}

void sgRotYMat4(SGmat4* m1, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    
    m1->m0 = cosTheta; m1->m4 = 0.0f; m1->m8 = sinTheta; m1->m12 = 0.0f;
    m1->m1 = 0.0f;    m1->m5 = 1.0f; m1->m9 = 0.0f;     m1->m13 = 0.0f;
    m1->m2 = -sinTheta; m1->m6 = 0.0f; m1->m10 = cosTheta; m1->m14 = 0.0f;
    m1->m3 = 0.0f;    m1->m7 = 0.0f; m1->m11 = 0.0f;     m1->m15 = 1.0f;
}

void sgRotZMat4(SGmat4* m1, float angle) {
    float cosTheta = cos(angle);
    float sinTheta = sin(angle);
    
    m1->m0 = cosTheta; m1->m4 = -sinTheta; m1->m8 = 0.0f; m1->m12 = 0.0f;
    m1->m1 = sinTheta; m1->m5 = cosTheta;  m1->m9 = 0.0f; m1->m13 = 0.0f;
    m1->m2 = 0.0f;     m1->m6 = 0.0f;      m1->m10 = 1.0f; m1->m14 = 0.0f;
    m1->m3 = 0.0f;     m1->m7 = 0.0f;      m1->m11 = 0.0f; m1->m15 = 1.0f;
}

void sgRotMat4(SGmat4* result, float angleX, float angleY, float angleZ) {
    // calculate sines and cosines of the angles
    float cosX = cos(angleX);
    float sinX = sin(angleX);
    float cosY = cos(angleY);
    float sinY = sin(angleY);
    float cosZ = cos(angleZ);
    float sinZ = sin(angleZ);

    SGmat4 rotX = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, cosX, -sinX, 0.0f,
        0.0f, sinX, cosX, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    SGmat4 rotY = {
        cosY, 0.0f, sinY, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        -sinY, 0.0f, cosY, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    SGmat4 rotZ = {
        cosZ, -sinZ, 0.0f, 0.0f,
        sinZ, cosZ, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    };

    // combine rotations: Z * Y * X
    SGmat4 temp = sgIdentity();
    sgMulMat4(&temp, rotZ, rotY); // combine Z and Y rotations
    sgMulMat4(result, temp, rotX); // combine with X rotation
}

