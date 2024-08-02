#pragma once

#include "smath.h"
#include "sutil.h"
#include "defines.h"
#include "../deps/GL/glew.h"
#include "../deps/GL/glfw3.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../deps/stb_image.h"

#define SGwindow GLFWwindow

// Custom draw modes
#define SG_CLEAR                                0x0000      // GL_LINES

// Primitive assembly draw modes
#define SG_LINES                                0x0001      // GL_LINES
#define SG_TRIANGLES                            0x0004      // GL_TRIANGLES
#define SG_QUADS                                0x0007      // GL_QUADS

// GL equivalent data types
#define SG_UNSIGNED_BYTE                        0x1401      // GL_UNSIGNED_BYTE
#define SG_FLOAT     

// GL Shader type
#define SG_FRAGMENT_SHADER                      0x8B30      // GL_FRAGMENT_SHADER
#define SG_VERTEX_SHADER                        0x8B31      // GL_VERTEX_SHADER
#define SG_COMPUTE_SHADER                       0x91B9      // GL_COMPUTE_SHADER

// GL Texture formats
#define SG_TEX2D_RGB                            0x1907      // GL_RGB
#define SG_TEX2D_RGBA                           0x1908      // GL_RGBA

// VERTEX ATTRIBUTE LOCATIONS
#define SG_VATTR_LOCATION_POS       0
#define SG_VATTR_LOCATION_TEX       1
#define SG_VATTR_LOCATION_COLOR     2
#define SG_VATTR_LOCATION_NORMAL    3

// VERTEX ATTRIBUTE SIZES
#define SG_NUM_POS_COMPONENTS 3
#define SG_NUM_TEX_COMPONENTS 2
#define SG_NUM_COLOR_COMPONENTS 3
#define SG_NUM_NORMAL_COMPONENTS 3

// VERTEX ATTRIBUTE BUFFER TYPES
#define SG_POS_ATTR_BUFFER SG_NUM_POS_COMPONENTS
#define SG_TEX_ATTR_BUFFER SG_NUM_TEX_COMPONENTS
#define SG_COLOR_ATTR_BUFFER SG_NUM_COLOR_COMPONENTS
#define SG_NORMAL_ATTR_BUFFER SG_NUM_NORMAL_COMPONENTS

// UNIFORMS
#define SG_UNIFORM_MAX 16
#define SG_UNIFORM_NAMESIZE 32

#define sgGetVeretxCount(__BUFFER, __ARR) (sizeof( __ARR ) / sizeof( __ARR[0] ) ) / ( ( __BUFFER * 2 ) / 2 )

SGshader defaultShader = {.program=-1};
SGvertexbuffer defaultBuffer = {.nverts=0, .vao=-1, .vbo={0,0,0,0}};
SGtexture2D defaultTex2D = {.glref=-1, .height=0, .width=0, .nchannels=0, .raw=NULL};

typedef struct SGcolor3 { u32 r, g, b; } SGcolor3;
typedef struct SGcolor4 { u32 r, g, b, a; } SGcolor4;

void sgFrameBufferCallback(SGwindow* win, int w, int h) {
    glViewport(0,0,w,h);
}

SGwindow* sgMakeWindow(u32 w, u32 h, char* title) {
    SGwindow* win = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!sgValidatePtr(win)) {
        sgLogError("Failed Create Window!");
        return NULL;
    } else {
        glfwMakeContextCurrent(win);
        glViewport(0, 0, w, h);
        glfwSetFramebufferSizeCallback(win, sgFrameBufferCallback);
        sgLogSuccess("Created Window!");

        GLenum res = glewInit();
        if (res != GLEW_OK) {
            fprintf(stderr, "Error: `%s`\n", glewGetErrorString(res));
        sgLogError("GLEW Initialization Failed!");
            return NULL;
        } else sgLogSuccess("GLEW Initialized!");

        // tell GL to only draw to a pixel if the shape is closer to the viewer
        glEnable(GL_DEPTH_TEST);	// enable depth-testing
        glDepthFunc(GL_LESS);		// depth-testing now interprets smaller values as `closer`

        return win;
    }
}

b8 sgShouldQuit(SGwindow* win) {
        if (glfwWindowShouldClose(win)) return 1;
        else return 0;
}

void sgPollEvents(void) {
        glfwPollEvents();
}

// BUFFERS
void sgMakeVertexArray(u32* handle) {
    glGenVertexArrays(1, handle);
    glBindVertexArray(*handle);
    unsigned int error = glGetError();
    if (error != GL_NO_ERROR) {
        sgLogError("OpenGL Error in sgMakeVertexArray: %d", error);
    }
    glBindVertexArray(0);
}

void sgMakeBuffer(u32* handle, unsigned int btype, void* data, i32 size) {
    glGenBuffers(1, handle);
    if (*handle == 0) {
        sgLogError("Failed to generate buffer.");
        return;
    }
    
    glBindBuffer(btype, *handle);
    glBufferData(btype, size, data, GL_STATIC_DRAW);
    
    unsigned int error = glGetError();
    if (error != GL_NO_ERROR) {
        sgLogError("OpenGL Error in sgMakeBuffer: %d", error);
    }

    glBindBuffer(btype, 0);
}

void sgConfigureVertexAttrib(u32 vao, u32 index, u32 acomponents, u32 vcomponents) {
    glBindVertexArray(vao);
    glVertexAttribPointer(
            index,
            acomponents,
            GL_FLOAT,
            GL_FALSE,
            sizeof(f32) * vcomponents,
            (void*)0
    );
    glEnableVertexAttribArray(index);
}

SGvertexbuffer sgMakeVertexBuffer(f32* verts, u32 vcount, f32* texCoords, u32 tcount) {
    SGvertexbuffer vbuffer;
    vbuffer.vao = -1;
    vbuffer.nverts = vcount;
        
    sgMakeBuffer(&vbuffer.vbo[SG_VATTR_LOCATION_POS], GL_ARRAY_BUFFER, verts, sizeof(f32) * ( SG_NUM_POS_COMPONENTS * vcount ));
    if (vbuffer.vbo[SG_VATTR_LOCATION_POS] == 0) {
        sgLogError("Error generating position vbo");
    }

    if (texCoords != NULL && tcount > 0) {
        sgMakeBuffer(&vbuffer.vbo[SG_VATTR_LOCATION_TEX], GL_ARRAY_BUFFER, texCoords, sizeof(f32) * ( SG_NUM_TEX_COMPONENTS * tcount ));
        if (vbuffer.vbo[SG_VATTR_LOCATION_TEX] == 0) {
            sgLogError("Error generating texture vbo");
        }
    } else { vbuffer.vbo[SG_VATTR_LOCATION_TEX] = SG_MESH_MAX; }

    vbuffer.vbo[SG_VATTR_LOCATION_COLOR] = SG_MESH_MAX;
    vbuffer.vbo[SG_VATTR_LOCATION_NORMAL] = SG_MESH_MAX;
    
    return vbuffer;
}

// SHADER
u32 sgCompileShader(u32 type, const char* source) {
    u32 shader = glCreateShader(type);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        sgLogError("SHADER :: COMPILATION FAILED :: %s", info_log);
    } else sgLogSuccess("SHADER :: COMPILATION SUCCESS");

    return shader;
}

u32 sgLinkShader(u32 vertex_shader, u32 fragment_shader) {
    u32 shader = glCreateProgram();
    glAttachShader(shader, vertex_shader);
    glAttachShader(shader, fragment_shader);
    glLinkProgram(shader);

    int success;
    char info_log[512];
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, info_log);
        sgLogError("SHADER ::LINKING FAILED :: %s", info_log);
    } else sgLogSuccess("SHADER :: LINKING SUCCESS");

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return shader;
}

SGshader sgMakeShader(const char* vertex_src, const char* fragment_src) {
    SGshader shader = {.program=-1};
    const char * vs = sgReadFile(vertex_src);
    const char * fs = sgReadFile(fragment_src);

    // try compiling directly from memory
    u32 vertex_shader = sgCompileShader(GL_VERTEX_SHADER, (vs != NULL) ? vs : vertex_src);
    u32 fragment_shader = sgCompileShader(GL_FRAGMENT_SHADER, (fs != NULL) ? fs : fragment_src);
    shader.program = sgLinkShader(vertex_shader, fragment_shader);
    return shader;
}

// UNIFORMS
typedef enum SGuniformtypes {
    SG_UNI_MAT4=0
} SGuniformtypes;

const GLfloat* sgValuePtr(const SGmat4* mat) {
    return (const GLfloat*)mat;
}

void sgUniformMat4(SGuniform* uniform) {
    if (uniform->data != NULL && uniform->type == SG_UNI_MAT4) {
        glUniformMatrix4fv(uniform->location, 1, GL_FALSE, (const GLfloat*)uniform->data);
    }
}

void sgSetUniforms(SGshader* shader) {
    for (int i = 0; i < 16; ++i) {
        SGuniform* uniform = &shader->uniforms[i];
        if (uniform->data == NULL) {
            continue;
        }
        switch (uniform->type) {
            case SG_UNI_MAT4:
                glUniformMatrix4fv(uniform->location, 1, GL_FALSE, (const GLfloat*)uniform->data);
                break;
            // case SG_UNI_VEC3:
            //     glUniform3fv(uniform->location, 1, (const GLfloat*)uniform->data);
            //     break;
            // TODO: add cases for other uniform types (e.g., SG_UNI_VEC2, SG_UNI_VEC4)
            default:
                break;
        }
    }
}


// TEXTURE
SGtexture2D sgMakeTexture2D(char* tex_src, u32 format) {
    SGtexture2D texture;
    
    glGenTextures(1, &texture.glref);
    if (texture.glref == -1) {
        sgLogError("failed to generate texture id");
        return defaultTex2D;
    }
    
    glBindTexture(GL_TEXTURE_2D, texture.glref);

    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    // load and generate the texture with the stbi header
    stbi_set_flip_vertically_on_load(SGTRUE);
    texture.raw = stbi_load(tex_src, &texture.width, &texture.height, &texture.nchannels, 0);
    if (texture.raw) {
            glTexImage2D(GL_TEXTURE_2D, 0, format, texture.width, texture.height, 0, format, GL_UNSIGNED_BYTE, texture.raw);
            glGenerateMipmap(GL_TEXTURE_2D);
    } else {
            sgLogError("failed to load texture data: src[%s]", tex_src);
            return defaultTex2D;
    }

    return texture;
}
