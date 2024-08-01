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
    if (config->texcoords != NULL && config->ntexcoords > 0) {
        sgLogInfo("Constructing mesh with texcoord count: %d", config->ntexcoords);
        config->vbuffer = sgMakeVertexBuffer(config->verts, config->nvertices, config->texcoords, config->ntexcoords);
    } else {
        sgLogInfo("Constructing mesh with no texcoords");
        config->vbuffer = sgMakeVertexBuffer(config->verts, config->nvertices, NULL, 0);
    }
    
    for (int i = 0; i < 4; i++) {
        if (config->vbuffer.vbo[i] == 0) {
            ccontext.target->err = 1;
            sgLogError("Error constructing a mesh: vbo generation failed");
            sgUnbindConstructor();
            return;
        }
    }
    config->verts = NULL;
    
    sgMakeVertexArray(&config->vbuffer.vao);
    if (config->vbuffer.vao == 0) {
        ccontext.target->err = 1;
        sgLogError("Error constructing a mesh: vao generation failed");
        sgUnbindConstructor();
        return;
    }
    
    glBindVertexArray(config->vbuffer.vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, config->vbuffer.vbo[SG_VATTR_LOCATION_POS]);
    sgConfigureVertexAttrib(config->vbuffer.vao, SG_VATTR_LOCATION_POS, 3, 3);  // position (location=0)
    
    if (config->texcoords != NULL && config->ntexcoords > 0) {
        glBindBuffer(GL_ARRAY_BUFFER, config->vbuffer.vbo[SG_VATTR_LOCATION_TEX]);
        sgConfigureVertexAttrib(config->vbuffer.vao, SG_VATTR_LOCATION_TEX, 2, 2);  // texcoords (location=1)
    }
    
    // glBindBuffer(GL_ARRAY_BUFFER, config->vbuffer.vbo[SG_VATTR_LOCATION_COLOR]);
    // sgConfigureVertexAttrib(config->vbuffer.vao, SG_VATTR_LOCATION_COLOR, 3, 3);  // color (location=2)
    
    // glBindBuffer(GL_ARRAY_BUFFER, config->vbuffer.vbo[SG_VATTR_LOCATION_NORMAL]);
    // sgConfigureVertexAttrib(config->vbuffer.vao, SG_VATTR_LOCATION_NORMAL, 3, 3);  // normals (location=3)

    glBindVertexArray(0);

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
    sgLogInfo("Constructing Shader from sources:\n%s\n%s", config->vertexShaderSource, config->fragmentShaderSource);
    config->shader = sgMakeShader(config->vertexShaderSource, config->fragmentShaderSource);
    if (config->shader.program == -1) {
        ccontext.target->err = 1;
        sgLogError("Error constructing a shader: program generation failed");
        return;
    }
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
    sgLogInfo("Constructing Texture from source: %s", config->src);
    config->texture2D = sgMakeTexture2D(config->src, config->format);
    if (config->texture2D.raw == NULL) {
        ccontext.target->err = 1;
        sgLogError("Error constructing texture: texture data failed to load");
        return;
    }

    // Pass to store context to store texture data
    sgStoreTexture((SGhandle*)ccontext.target);
    #ifndef SOGL_MANUAL_CONTEXT
        sgUnbindConstructor();
    #endif
}



