#pragma once

#include "../sgl.h"
#include "../sutil.h"
#include "../defines.h"

typedef struct SGgcontext {
    bool bound;
    SGhandle* target;
    unsigned int next[SG_RESOURCE_TYPES];
} SGgcontext;
static SGgcontext gcontext = {.bound=false, .target=NULL};

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

SGhandle sgGenHandle(u32 htype, ...) {
    va_list args;
    va_start(args, htype);
    SGhandle handle = {0};
    switch(htype) {
        case SG_MESH: handle =    sgGenMesh(args);      break;
        case SG_SHADER: handle =  sgGenShader(args);    break;
        case SG_TEXTURE: handle = sgGenTexture(args);   break;
        default: sgLogInfo("Unknown handle type");      break;
    }
    va_end(args);
    return handle;
}

// the user should never call this!!!
SGhandle sgGenMesh(va_list args) {
    float* verts = va_arg(args, float*);
    unsigned int nverts = va_arg(args, unsigned int);
    float* texcoords = va_arg(args, float*);
    unsigned int ntexcoords = va_arg(args, unsigned int);
    SGmeshconfig* mconfig = malloc(sizeof(SGmeshconfig));
    if (!mconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
        return (SGhandle){0};
    }
    mconfig->nvertices = nverts;
    mconfig->ntexcoords = ntexcoords;
    mconfig->verts = malloc(SG_NUM_POS_COMPONENTS * sizeof(float) * nverts);
    if (!mconfig->verts) {
        sgLogInfo("Failed to allocate memory for vertices!");
        free(mconfig);
        return (SGhandle){0};
    }
    
    memcpy(mconfig->verts, verts, SG_NUM_POS_COMPONENTS * sizeof(float) * nverts);
    if (!mconfig->verts) {
        sgLogInfo("Failed to allocate memory for vertices!");
        free(mconfig);
        return (SGhandle){0};
    }
    
    mconfig->texcoords = malloc(SG_NUM_TEX_COMPONENTS * sizeof(float) * ntexcoords);
    if (!mconfig->texcoords) {
        sgLogInfo("Failed to allocate memory for texcoords!");
        free(mconfig);
        return (SGhandle){0};
    }
    
    memcpy(mconfig->texcoords, texcoords, SG_NUM_TEX_COMPONENTS * sizeof(float) * ntexcoords);
    if (!mconfig->texcoords) {
        sgLogInfo("Failed to allocate memory for texcoords!");
        free(mconfig);
        return (SGhandle){0};
    }
    
    SGhandle mhandle = {.id=gcontext.next[SG_MESH]++, .err=0, .type=SG_MESH, .config=mconfig, .enabled=0};
    sgBindGenerator(&mhandle);
    return mhandle;
}

// the user should never call this!!!
// Params: Vertex Source, Fragment Source, Array of Uniform Names
SGhandle sgGenShader(va_list args) {
    const char* vert_src = va_arg(args, const char*);
    const char* frag_src = va_arg(args, const char*);

    char** uniforms = va_arg(args, char**);
    u32 nuniforms = va_arg(args, u32);

    SGshaderconfig* sconfig = malloc(sizeof(SGshaderconfig));
    if (!sconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
        return (SGhandle){0};
    }

    sconfig->uniforms = uniforms;
    sconfig->vertexShaderSource = vert_src;
    sconfig->fragmentShaderSource = frag_src;
    SGhandle shandle = {.id=gcontext.next[SG_SHADER]++, .err=0, .type=SG_SHADER, .config=sconfig, .enabled=0};
    sgBindGenerator(&shandle);
    return shandle;
}

// the user should never call this!!!
SGhandle sgGenTexture(va_list args) {
    char* src = va_arg(args, char*);
    unsigned int format = va_arg(args, unsigned int);
    SGtexconfig* tconfig = malloc(sizeof(SGtexconfig));
    if (!tconfig) {
        sgLogInfo("Failed to allocate memory for handle configuration");
        return (SGhandle){0};
    }
    tconfig->src = src;
    tconfig->format = format;
    SGhandle thandle = {.id=gcontext.next[SG_TEXTURE]++, .err=0, .type=SG_TEXTURE, .config=tconfig, .enabled=0};
    sgBindGenerator(&thandle);
    return thandle;
}
