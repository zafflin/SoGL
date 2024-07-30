#pragma once

#include "smath.h"
#include "sutil.h"
#include "defines.h"
#include "../deps/GL/glew.h"
#include "../deps/GL/glfw3.h"

#define SGwindow GLFWwindow

#define SG_NUM_VERTEX_COMPONENTS 3
#define sgGetVeretxCount(__ARR) (sizeof( __ARR ) / sizeof( __ARR[0] ) ) / ( ( SG_NUM_VERTEX_COMPONENTS * 2 ) / 2 )

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

SGshader defaultShader = {.program=-1};
SGvertexbuffer defaultBuffer = {.nverts=0, .vao=-1, .vbo=-1};

void sgFrameBufferCallback(SGwindow* win, int w, int h) {
    glViewport(0,0,w,h);
}

SGwindow* sgMakeWindow(u32 w, u32 h, char* title) {
    SGwindow* win = glfwCreateWindow(w, h, title, NULL, NULL);
    if (!sgValidate(win)) {
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
void sgMakeVertexArray(u32* handle, u32 vbo) {
	glGenVertexArrays(1, handle);
    glBindVertexArray(*handle);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindVertexArray(0);
}

void sgConfigureVertexAttrib(u32 vao, u32 index, u32 acomponents, u32 vcomponents) {
    glBindVertexArray(vao);
    glVertexAttribPointer(
            0,
            3,
            GL_FLOAT,
            GL_FALSE,
            sizeof(f32) * 3,
            (void*)0
    );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}

SGvertexbuffer sgMakeVertexBuffer(f32* verts, u32 vcount) {
    SGvertexbuffer vbuffer;
    vbuffer.vbo = -1;
    vbuffer.vao = -1;
    vbuffer.nverts = vcount;
    
    glGenBuffers(1, &vbuffer.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbuffer.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(f32) * ( SG_NUM_VERTEX_COMPONENTS * vcount ), verts, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
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
    u32 vertex_shader = sgCompileShader(GL_VERTEX_SHADER, sgReadFile(vertex_src));
    u32 fragment_shader = sgCompileShader(GL_FRAGMENT_SHADER, sgReadFile(fragment_src));
    shader.program = sgLinkShader(vertex_shader, fragment_shader);
    return shader;
}

