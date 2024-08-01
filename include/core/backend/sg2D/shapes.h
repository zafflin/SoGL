#pragma once

#include "../../sgl.h"
#include "../../defines.h"

static SGhandle sgQuad;
static SGhandle sgTriangle;
static b8 _initialized;

#ifdef SG_INIT_2D_SHAPES
    void sgInit2D(void) {
        f32 quad[] = {
            0.5f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,

            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f,
            0.5f,  0.5f, 0.0f};
        sgQuad = sgGenMesh(quad, sgGetVeretxCount(quad));
        sgBindConstructor(&sgQuad);

        f32 triangle[] = {
            0.0+0.5f,  0.5f, 0.0f,
            0.5+0.5f, -0.5f, 0.0f,
            -0.5+0.5f, -0.5f, 0.0f};
        sgTriangle = sgGenMesh(triangle, sgGetVeretxCount(triangle));
        sgBindConstructor(&sgTriangle);
    }
#else
    void sgInit2D(void) {

    }
#endif

SGdrawcall* sgDrawQuad(SGhandle* shandle) {
    #ifdef SG_INIT_2D_SHAPES
        return sgDrawCall(&sgQuad, shandle);
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
            mhandle = sgGenMesh(quad, sgGetVeretxCount(quad));
            sgBindConstructor(&mhandle);
        }
        if (mhandle.id >= 0 && !mhandle.err) { genquad = 1; }
        return sgDrawCall(&mhandle, shandle);
    #endif
}

SGdrawcall* sgDrawTriangle(SGhandle* shandle) {
    #ifdef SG_INIT_2D_SHAPES
        return sgDrawCall(&sgTriangle, shandle);
    #else
        static b8 gentriangle = 0;
        static SGhandle mhandle = {0};
        f32 triangle[] = {
            0.0f,  0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f};
        
        if (gentriangle == 0) {
            mhandle = sgGenMesh(triangle, sgGetVeretxCount(triangle));
            sgBindConstructor(&mhandle);
        }
        if (mhandle.id >= 0 && !mhandle.err) { gentriangle = 1; }
        return sgDrawCall(&mhandle, shandle);
    #endif
}