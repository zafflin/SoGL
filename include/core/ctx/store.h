#pragma once

#include "../sutil.h"
#include "../defines.h"

typedef struct SGscontext {
    bool bound;
    SGhandle* target;
} SGscontext;
static SGscontext scontext = {.bound=SGFALSE, .target=NULL};

typedef struct TextureBlock {
    bool init;
    unsigned int max;
    unsigned int num;
    unsigned char* raw[SG_TEXTURE_MAX];
    unsigned int glref[SG_TEXTURE_MAX];
    unsigned int width[SG_TEXTURE_MAX];
    unsigned int height[SG_TEXTURE_MAX];
} TextureBlock;
static TextureBlock tblock;

typedef struct MeshBlock {
    bool init;
    unsigned int max;
    unsigned int num;
    unsigned int *vbo[SG_MESH_MAX];
    unsigned int ebo[SG_MESH_MAX];
    unsigned int vao[SG_MESH_MAX];
} MeshBlock;
static MeshBlock mblock;

typedef struct ShaderBlock {
    bool init;
    unsigned int max;
    unsigned int num;
    unsigned int program[SG_SHADER_MAX];
} ShaderBlock;
static ShaderBlock sblock;

// STORE CONTEXT
// the user should never call this!!!
void sgBindStore(SGhandle* target) {
    if (scontext.bound && target == NULL) {
        sgUnbindStore();
    } else if (!scontext.bound && !target->err) {
        scontext.bound = true;
        scontext.target = target;
        
        char handlestr[50];
        sgGetHandleStr(target, handlestr);
        sgLogInfo("Handle bound to Store: %s [%d]", handlestr, target->id);
    }
}

// the user should never call this!!!
void sgUnbindStore(void) {
    if (scontext.bound) {
        scontext.bound = SGFALSE;
        
        char handlestr[50];
        sgGetHandleStr(scontext.target, handlestr);
        sgLogInfo("Handle un-bound from Store: %s [%d]", handlestr, scontext.target->id);
        scontext.target = NULL;
    }
}

void sgInitResourceBlock(ResourceType type) {
    switch (type) {
        case (SG_MESH):
            mblock.max = SG_MESH_MAX;
            mblock.num = 0;
            mblock.init = true;

            for (int i = 0; i < SG_MESH_MAX; i++) {
                mblock.vbo[i] = (u32*)malloc(sizeof(u32)*4);
                if (mblock.vbo[i] == NULL) {
                    sgLogError("Error allocating memory for mesh block vbo field");
                    return;
                }
            }
            break;
        case (SG_SHADER):
            sblock.max = SG_SHADER_MAX;
            sblock.num = 0;
            sblock.init = true;
            break;
        case (SG_TEXTURE):
            tblock.max = SG_TEXTURE_MAX;
            tblock.num = 0;
            tblock.init = true;
            
            for (int i = 0; i < SG_TEXTURE_MAX; i++) {
                tblock.raw[i] = (char*)malloc(sizeof(char*)*2048);
                if (tblock.raw[i] == NULL) {
                    sgLogError("Error allocating memory for texture block raw data field");
                    return;
                }
            }
            break;
        default:
            break;
    }
}

void sgStoreMesh(SGhandle* handle) {
    if (!mblock.init) {
        sgLogInfo("RESOURCE BLOCK NOT INITIALIZED!");
        return;
    }

    if (!handle->err && handle->type == SG_MESH) {
        sgBindStore(handle);
        unsigned int index = handle->id;
        if (mblock.num+1 < mblock.max) {
            SGmeshconfig* config = (SGmeshconfig*)handle->config;
            sgLogInfo("STORING MESH: VERTEX: %d | VBO: %d", config->vbuffer.nverts, config->vbuffer.vbo[0]);
            mblock.vao[index] = config->vbuffer.vao;
            
            for (int i = 0; i < 4; i++) {
                if (config->vbuffer.vbo[i] == -1) { return; } else mblock.vbo[index][i] = config->vbuffer.vbo[i];
            }
            mblock.num++;
            sgLogInfo("STORED MESH: [%d] COUNT: [%d] MAX: [%d]", index, mblock.num, mblock.max);
        }
    }
}

void sgStoreShader(SGhandle* handle) {
    if (!sblock.init) {
        sgLogInfo("RESOURCE BLOCK NOT INITIALIZED!");
        return;
    }

    if (!handle->err && handle->type == SG_SHADER) {
        sgBindStore(handle);
        unsigned int index = handle->id;
        if (sblock.num+1 < sblock.max) {
            SGshaderconfig* config = (SGshaderconfig*)handle->config;
            sgLogInfo("STORING SHADER: [%d] COUNT: [%d] MAX: [%d]", index, sblock.num, sblock.max);
            sblock.program[index] = config->shader.program;
            sblock.num++;
            sgLogInfo("STORED SHADER: [%d] PROGRAM: [%d] COUNT: [%d] MAX: [%d]", index, sblock.program[index], sblock.num, sblock.max);
        }
    }
}

void sgStoreTexture(SGhandle* handle) {
        if (!tblock.init) {
        sgLogInfo("RESOURCE BLOCK NOT INITIALIZED!");
        return;
    }

    if (!handle->err && handle->type == SG_TEXTURE) {
        sgBindStore(handle);
        unsigned int index = handle->id;
        if (tblock.num+1 < tblock.max) {
            
            SGtexconfig* config = (SGtexconfig*)handle->config;
            
            sgLogInfo("STORING TEXTURE: [%d] COUNT: [%d] MAX: [%d]", index, tblock.num, tblock.max);
            
            memcpy(tblock.raw[index], config->texture2D.raw, sizeof(config->texture2D.raw));
            if (config->texture2D.raw == NULL) {
                handle->err=1;
                sgLogError("Error allocating memory for raw texture data."); 
            }
            
            tblock.glref[index] = config->texture2D.glref;
            tblock.width[index] = config->texture2D.width;
            tblock.height[index] = config->texture2D.height;
            
            // stbi_image_free(config->texture2D.raw);

            tblock.num++;
            sgLogInfo("STORED TEXTURE: [%d] COUNT: [%d] MAX: [%d]", index, tblock.num, tblock.max);
        }
    }
}

