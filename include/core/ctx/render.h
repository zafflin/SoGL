#pragma once

#include "../sgl.h"
#include "../smath.h"
#include "../defines.h"

struct SGdrawcall {
    unsigned int err;
    int vao;
    int texID;
    int shader;
    unsigned int nvertices;
};
static SGdrawcall defaultCall = {.vao=-1, .texID=-1, .shader=-1, .nvertices=0};

typedef struct SGrcontext {
    bool bound;
    SGvec4 clearcolor;
    unsigned int mode;
    unsigned int npass;     // number of render passes (cycles)
    SGdrawcall* call;
} SGrcontext;
static SGrcontext rcontext = {.bound=SGFALSE, .clearcolor=(SGvec4){0.0f, 0.0f, 0.0f, 0.0f}, .mode=SG_CLEAR, .npass=0, .call=&defaultCall};

void sgGetRenderModeStr(char* str) {
    if (rcontext.mode == SG_LINES) sprintf(str, "SG_LINES");
    else if (rcontext.mode == SG_QUADS) sprintf(str, "SG_QUADS");
    else if (rcontext.mode == SG_CLEAR) sprintf(str, "SG_CLEAR");
    else sprintf(str, "SG_TRIANGLES");
}

// RENDER CONTEXT
void sgBindRender(SGdrawcall* call) {
    if (rcontext.bound && call == NULL) {
        sgUnbindRender();
    } else if (!rcontext.bound && !call->err) {
        rcontext.call = call;
        rcontext.bound = SGTRUE;
    } else sgLogError("INVALID DRAW CALL DATA FOR PASS: %d\n", rcontext.npass);
}

void sgUnbindRender() {
    if (rcontext.bound) {
        rcontext.bound = false;
        rcontext.call = NULL;
    }
}

// configure render context, and draw call state before rendering
void sgBeginRender(u32 mode) {
    rcontext.mode = mode;
    SGdrawcall* call = rcontext.call;
    if (rcontext.bound) {
        char msg[1024], modestr[1024];
        sgGetRenderModeStr(modestr);
        sprintf(
            msg,
            "Setup Render For Draw Call:\nMODE: %s\nVAO: %d\nTEXID: %d\nSHADER: %d\nVERTICES: %d\n",
            modestr, rcontext.call->vao, rcontext.call->texID, rcontext.call->shader, rcontext.call->nvertices
        );
        // sgLogInfo("%s",msg);
    }
}

SGdrawcall sgDrawCall(SGhandle mhandle, SGhandle shandle) {
    SGdrawcall call = defaultCall;
    if (!mhandle.err && !shandle.err && mhandle.type == SG_MESH) {
        SGmeshconfig mconfig = *(SGmeshconfig*)mhandle.config;
        SGshaderconfig sconfig = *(SGshaderconfig*)shandle.config;
        call = (SGdrawcall) {
            .vao=mconfig.vbuffer.vao,
            .texID=0,
            .shader=sconfig.shader.program,
            .nvertices=mconfig.nvertices
        };
        // sgLogSuccess("GENERATED DRAW CALL\n");
    } else sgLogError("FAILED TO GENERATE DRAW CALL FOR GIVEN DATA\n");
    // sgLogInfo("SENDING DRAW CALL\n");
    return call;
};

void sgClearColor(f32 r, f32 g, f32 b, f32 a) {
    rcontext.clearcolor.x=r/255.0f;
    rcontext.clearcolor.y=g/255.0f;
    rcontext.clearcolor.z=b/255.0f;
    rcontext.clearcolor.w=a/255.0f;
}

void sgRender(SGdrawcall call) {
    // sgLogInfo("BINDING DRAW CALL TO RENDER CONTEXT\n");
    sgBindRender(&call);
    // sgLogInfo("DRAW CALL BOUND TO RENDER CONTEXT\n");
    glClearColor(rcontext.clearcolor.x, rcontext.clearcolor.y, rcontext.clearcolor.z, rcontext.clearcolor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindTexture(GL_TEXTURE_2D, call.texID);
    glUseProgram(call.shader);
    glBindVertexArray(call.vao);
    glDrawArrays(rcontext.mode, 0, call.nvertices);
    rcontext.npass++;
}

// clean up render context, and draw call state after rendering
void sgEndRender(void* window) {
    glfwSwapBuffers((SGwindow*)window);
    // sgLogInfo("UN-BINDING DRAW CALL FROM RENDER CONTEXT\n");
    sgUnbindRender();
    // sgLogInfo("DRAW CALL UN-BOUND FROM RENDER CONTEXT\n");
}

