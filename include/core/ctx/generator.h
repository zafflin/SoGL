#pragma once

#include "../sgl.h"
#include "../sutil.h"
#include "../defines.h"

typedef struct SGgcontext {
    int next;
    bool bound;
    SGhandle* target;
} SGgcontext;
static SGgcontext gcontext = {.bound=false, .target=NULL, .next=0};

// GENERATOR CONTEXT
// the user should never call this!!!
void sgBindGenerator(SGhandle* target) {
    if (gcontext.bound && target == NULL) {
        sgUnbindGenerator();
    } else if (!gcontext.bound && !target->err) {
        gcontext.bound = SGTRUE;
        gcontext.target = target;
        
        char handlestr[50];
        sgGetHandleStr(target, handlestr);
        sgLogInfo("Handle bound to Generator: %s [%d]", handlestr, target->id);
    }
}

// the user should never call this!!!
void sgUnbindGenerator(void) {
    if (gcontext.bound) {
        gcontext.bound = false;
        
        char handlestr[50];
        sgGetHandleStr(gcontext.target, handlestr);
        sgLogInfo("Handle un-bound from Generator: %s [%d]", handlestr, gcontext.target->id);
        
        gcontext.target = NULL;
    }
}

SGhandle sgGenTexture(char* src) {
    SGtexconfig* tconfig = malloc(sizeof(SGtexconfig));
    tconfig->src = src; 
    tconfig->width=0; 
    tconfig->height=0;
    if (!tconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
    }
    SGhandle thandle = {.id=gcontext.next++, .err=0, .type=SG_TEXTURE, .config=tconfig, .enabled=0};
    sgBindGenerator(&thandle);
    return thandle;
}

SGhandle sgGenShader(const char* vert_src, const char* frag_src) {
    SGshaderconfig* sconfig = malloc(sizeof(SGshaderconfig));
    if (!sconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
    }
    sconfig->vertexShaderSource = vert_src;
    sconfig->fragmentShaderSource = frag_src;
    SGhandle shandle = {.id=gcontext.next++, .err=0, .type=SG_SHADER, .config=sconfig, .enabled=0};
    sgBindGenerator(&shandle);
    return shandle;
}

SGhandle sgGenMesh(float* verts, unsigned int nverts) {
    SGmeshconfig* mconfig = malloc(sizeof(SGmeshconfig));
    if (!mconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
    }

    mconfig->nvertices = nverts;

    mconfig->_vtemp = malloc(SG_NUM_VERTEX_COMPONENTS * sizeof(float) * nverts);
    if (mconfig->_vtemp == NULL) {
        sgLogInfo("Failed to allocate memory for vertices!");
    }
    memcpy(mconfig->_vtemp, verts, SG_NUM_VERTEX_COMPONENTS * sizeof(float) * nverts);
    if (mconfig->_vtemp == NULL) {
        sgLogInfo("Failed to set memory for vertices!");
    }
    
    SGhandle mhandle = {.id=gcontext.next++, .err=0, .type=SG_MESH, .config=mconfig, .enabled=0};
    sgBindGenerator(&mhandle);
    return *gcontext.target;
}

