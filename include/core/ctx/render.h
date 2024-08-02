#pragma once

#include "../sgl.h"
#include "../smath.h"
#include "../defines.h"

static SGdrawcall defaultCall = {.vao=-1, .texID=-1, .shader=-1, .nvertices=0};

typedef struct SGrcontext {
    bool bound;
    SGvec4 clearcolor;
    unsigned int mode;
    unsigned int npass;     // number of render passes (cycles)
    unsigned int drawcalls; // number of draw calls recieved
    SGdrawcall* call;
} SGrcontext;
static SGrcontext rcontext = {.bound=SGFALSE, .clearcolor=(SGvec4){0.0f, 0.0f, 0.0f, 0.0f}, .mode=SG_CLEAR, .npass=0, .call=NULL, .drawcalls=0};

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
    } else if (!rcontext.bound && call != NULL) {
        rcontext.call = call;
        rcontext.bound = SGTRUE;
    }
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
    glClearColor(rcontext.clearcolor.x, rcontext.clearcolor.y, rcontext.clearcolor.z, rcontext.clearcolor.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

SGdrawcall* sgDrawCall(const SGhandle* mhandle, const SGhandle* shandle, const SGhandle* thandle) {
    SGdrawcall* call = &defaultCall;
    b8 hasTexture = 0;
    if (thandle != NULL && !thandle->err) hasTexture=1;
    if (mhandle && !mhandle->err && !shandle->err && mhandle->type == SG_MESH) {
        SGmeshconfig mconfig = *(SGmeshconfig*)mhandle->config;
        SGshaderconfig sconfig = *(SGshaderconfig*)shandle->config;
        call->err=0;
        call->vao=mconfig.vbuffer.vao;
        if (hasTexture == 1) {
            SGtexconfig tconfig = *(SGtexconfig*)thandle->config;
            call->texID=tconfig.texture2D.glref;
        } else {
            call->texID=0;
        }
        call->shader=sconfig.shader;
        call->nvertices=mconfig.nvertices;
        // sgLogSuccess("GENERATED DRAW CALL\n");
    }// else sgLogError("FAILED TO GENERATE DRAW CALL FOR GIVEN DATA\n");
    // sgLogInfo("SENDING DRAW CALL\n");
    return call;
};

void sgClearColor(f32 r, f32 g, f32 b, f32 a) {
    rcontext.clearcolor.x=r/255.0f;
    rcontext.clearcolor.y=g/255.0f;
    rcontext.clearcolor.z=b/255.0f;
    rcontext.clearcolor.w=a/255.0f;
}

void sgRender(SGdrawcall* call) {
    // sgLogInfo("BINDING DRAW CALL TO RENDER CONTEXT\n");
    sgBindRender(call); rcontext.drawcalls++;
    // sgLogInfo("DRAW CALL BOUND TO RENDER CONTEXT\n");
    glBindTexture(GL_TEXTURE_2D, call->texID);
    glUseProgram(call->shader.program);
    // TODO: set uniforms from uniform structure data
    glBindVertexArray(call->vao);
    glDrawArrays(rcontext.mode, 0, call->nvertices);
    rcontext.npass++;
}

// clean up render context, and draw call state after rendering
void sgEndRender(void* window) {
    glfwSwapBuffers((SGwindow*)window);
    // sgLogInfo("UN-BINDING DRAW CALL FROM RENDER CONTEXT\n");
    sgUnbindRender();
    // sgLogInfo("DRAW CALL UN-BOUND FROM RENDER CONTEXT\n");
}

