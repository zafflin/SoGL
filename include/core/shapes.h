#pragma once

#include "sgl.h"
#include "defines.h"

static SGhandle sgQuad;
static SGhandle sgTriangle;
static b8 _initialized;

#ifdef SG_PREGENERATE
    void sgInit2D(void) {
        f32 quad[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,

            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f};

        f32 qtexcoords[] = {
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,

            0.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f};

        sgQuad = sgGenHandle(SG_MESH, quad, sgGetVeretxCount(SG_POS_ATTR_BUFFER, quad), qtexcoords, sgGetVeretxCount(SG_TEX_ATTR_BUFFER, qtexcoords));
        sgBindConstructor(&sgQuad);

        f32 triangle[] = {
            0.0,  0.5f, 0.0f,
            0.5, -0.5f, 0.0f,
            -0.5, -0.5f, 0.0f};
        
        f32 ttexcoords[] = {
            0.5f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f};
        sgTriangle = sgGenHandle(SG_MESH, triangle, sgGetVeretxCount(SG_POS_ATTR_BUFFER, triangle), ttexcoords, sgGetVeretxCount(SG_TEX_ATTR_BUFFER, ttexcoords));
        sgBindConstructor(&sgTriangle);
    }
#else
    void sgInit2D(void) {

    }
#endif

SGdrawcall* sgDrawQuad(SGhandle* shandle, SGhandle* thandle) {
    #ifdef SG_PREGENERATE
        return sgDrawCall(&sgQuad, shandle, thandle);
    #else
        static b8 genquad = 0;
        static SGhandle mhandle = {0};
        f32 quad[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,

            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f};
        
        if (genquad == 0) {
            mhandle = sgGenHandle(SG_MESH, quad, sgGetVeretxCount(SG_POS_ATTR_BUFFER, quad), NULL, 0);
            sgBindConstructor(&mhandle);
        }
        if (mhandle.id >= 0 && !mhandle.err) { genquad = 1; }
        return sgDrawCall(&mhandle, shandle, thandle);
    #endif
}

SGdrawcall* sgDrawTriangle(SGhandle* shandle, SGhandle* thandle) {
    #ifdef SG_PREGENERATE
        return sgDrawCall(&sgTriangle, shandle, thandle);
    #else
        static b8 gentriangle = 0;
        static SGhandle mhandle = {0};
        f32 triangle[] = {
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f};
        
        if (gentriangle == 0) {
            mhandle = sgGenHandle(SG_MESH, triangle, sgGetVeretxCount(SG_POS_ATTR_BUFFER, triangle), NULL, 0);
            sgBindConstructor(&mhandle);
        }
        if (mhandle.id >= 0 && !mhandle.err) { gentriangle = 1; }
        return sgDrawCall(&mhandle, shandle, thandle);
    #endif
}

