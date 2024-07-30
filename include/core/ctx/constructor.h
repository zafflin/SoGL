#pragma once

#include "../sgl.h"
#include "../defines.h"

typedef struct SGccontext {
    bool bound;
    SGhandle* target;
} SGccontext;
static SGccontext ccontext = {.bound=SGFALSE, .target=NULL};

// CONSTRUCTOR CONTEXT
void* sgBindConstructor(SGhandle* target) {
    #ifndef SOGL_MANUAL_CONTEXT
        sgUnbindGenerator();
    #endif

    if (ccontext.bound && target == NULL) {
        sgUnbindConstructor();
    } else if (!ccontext.bound && !target->err) {
        ccontext.bound = true;
        ccontext.target = target;
        
        char handlestr[50];
        sgGetHandleStr(target, handlestr);
        sgLogInfo("Handle bound to Constructor: %s [%d]", handlestr, target->id);

        #ifndef SOGL_MANUAL_CONTEXT     // someone's getting fancy!
            switch (target->type) {
                case SG_MESH:
                    sgConstMesh();
                    break;
                case SG_SHADER: 
                    sgConstShader();
                    break;
                case SG_TEXTURE: 
                    sgConstTexture();
                    break;
                default: break;
            }
        #endif
    };
}

void sgUnbindConstructor(void) {
    if (ccontext.bound) {
        ccontext.bound = SGFALSE;
        
        char handlestr[50];
        sgGetHandleStr(ccontext.target, handlestr);
        sgLogInfo("Handle un-bound from Constructor: %s [%d]", handlestr, ccontext.target->id);
        // free(ccontext.target->config);
        ccontext.target = NULL;
        #ifndef SOGL_MANUAL_CONTEXT
            sgUnbindStore();
        #endif
    }
}

void sgConstMesh(void) {
    // Process mesh data based on config
    SGmeshconfig* config = (SGmeshconfig*)ccontext.target->config;

    // Allocate and populate data here
    config->vbuffer = sgMakeVertexBuffer(config->_vtemp, config->nvertices);        // TODO: catch error here
    sgMakeVertexArray(&config->vbuffer.vao, config->vbuffer.vbo);
    // TODO: make index and acomponents based on an SGvertextype (SG_VERTEX_POS, SG_VERTEX_TEX, SG_VERTEX_NORMAL, SG_VERTEX_COLOR)
    sgConfigureVertexAttrib(config->vbuffer.vao, 0, 3, 3);
    
    config->_vtemp = NULL;
    
    // Pass to store context to store texture data
    sgStoreMesh((SGhandle*)ccontext.target);
    #ifndef SOGL_MANUAL_CONTEXT
        sgUnbindConstructor();
    #endif
}

void sgConstShader(void) {
    // Process shader data based on config
    SGshaderconfig* config = (SGshaderconfig*)ccontext.target->config;
    // Allocate and populate data here
    sgLogInfo("Constructing Shader with sources: %s | %s", config->vertexShaderSource, config->fragmentShaderSource);
    config->shader = sgMakeShader(config->vertexShaderSource, config->fragmentShaderSource);
    // Pass to store context to store texture data
    sgStoreShader((SGhandle*)ccontext.target);
    #ifndef SOGL_MANUAL_CONTEXT
        sgUnbindConstructor();
    #endif
}

void sgConstTexture(void) {
    // Process texture data based on config
    SGtexconfig* config = (SGtexconfig*)ccontext.target->config;
    
    // Allocate and populate data here (load texture data)
    sgLogInfo("Constructing Texture with width %d and height %d", config->width, config->height);

    // Pass to store context to store texture data
    sgStoreTexture((SGhandle*)ccontext.target);
    #ifndef SOGL_MANUAL_CONTEXT
        sgUnbindConstructor();
    #endif
}



