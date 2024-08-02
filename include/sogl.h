#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "core/ctx/generator.h"
#include "core/ctx/constructor.h"
#include "core/ctx/store.h"
#include "core/ctx/render.h"
#include "core/sgl.h"
#include "core/shapes.h"
// #include "core/backend/sg3D"

#define SG_MALLOC(sz) malloc(sz);

struct SGcontext {
  struct info {
    u32 support_stereo_rendering;
    u32 max_draw_buffers;
    u32 max_texture_size;
    u32 max_viewport_dims;
    u32 max_vertex_attribs;
    u32 max_component_passes;
    u32 max_fragment_textures;
    u32 max_vertex_uniforms;
    u32 max_cubemap_texture_size;
    u32 max_vertex_textures;
    u32 max_shader_textures;
    u32 max_fragment_uniforms;
    char version[1024];
    const GLubyte* renderer;
  } info;

  struct {
    b8 running;
  } state;
  
  struct {
    char* title;
    SGvec2 winsize;
    SGwindow* window;
  } resources;
  b8 init;
};
static SGcontext SOGL;
static SGhandle sgDefaultShader = {0};

void sgContextDebug(const SGcontext *ctx) {
	sgLogInfo("SGcontext debug");
	sgLogInfo("---------------------------");
    sgLogInfo("GL version :: %s", ctx->info.version);
    sgLogInfo("GL renderer :: %s", ctx->info.renderer);
	sgLogInfo("---------------------------");
    sgLogInfo("max texture size :: %d", ctx->info.max_texture_size);
    sgLogInfo("max draw buffers :: %d", ctx->info.max_draw_buffers);
    sgLogInfo("max viewport dims :: %d", ctx->info.max_viewport_dims);
	sgLogInfo("---------------------------");
    sgLogInfo("max vertex attribs :: %d", ctx->info.max_vertex_attribs);
    sgLogInfo("max vertex uniforms :: %d", ctx->info.max_vertex_uniforms);
    sgLogInfo("max vertex textures :: %d", ctx->info.max_vertex_textures);
	sgLogInfo("---------------------------");
    sgLogInfo("max shader textures :: %d", ctx->info.max_shader_textures);
    sgLogInfo("max component passes :: %d", ctx->info.max_component_passes);
	sgLogInfo("---------------------------");
    sgLogInfo("max fragment uniforms :: %d", ctx->info.max_fragment_uniforms);
    sgLogInfo("max fragment textures :: %d", ctx->info.max_fragment_textures);
	sgLogInfo("---------------------------");
    sgLogInfo("max cubemap texture size :: %d", ctx->info.max_cubemap_texture_size);
    sgLogInfo("stero rendering support :: %d", ctx->info.support_stereo_rendering);
	sgLogInfo("---------------------------");
}

void soglInit(void) {
    if (!glfwInit()) {
        sgLogError("glfwInit");
	} else {
        sgLogSuccess("GLFW Initialized");
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }

    SOGL.resources.title = "SoGL : [Simply OpenGL]";
    SOGL.resources.winsize = (SGvec2){800.0, 600.0};
    SOGL.resources.window = sgMakeWindow(SOGL.resources.winsize.x, SOGL.resources.winsize.y, SOGL.resources.title);

    SOGL.info.support_stereo_rendering = GL_STEREO;
    SOGL.info.max_draw_buffers = GL_MAX_DRAW_BUFFERS;
    SOGL.info.max_texture_size = GL_MAX_TEXTURE_SIZE;
    SOGL.info.max_viewport_dims = GL_MAX_VIEWPORT_DIMS;
    SOGL.info.max_vertex_attribs = GL_MAX_VERTEX_ATTRIBS;
    SOGL.info.max_component_passes = GL_MAX_VARYING_FLOATS;
    SOGL.info.max_fragment_textures = GL_MAX_TEXTURE_IMAGE_UNITS;
    SOGL.info.max_vertex_uniforms = GL_MAX_VERTEX_UNIFORM_COMPONENTS;
    SOGL.info.max_cubemap_texture_size = GL_MAX_CUBE_MAP_TEXTURE_SIZE;
    SOGL.info.max_vertex_textures = GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS;
    SOGL.info.max_shader_textures = GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS;
    SOGL.info.max_fragment_uniforms = GL_MAX_FRAGMENT_UNIFORM_COMPONENTS;

    int major, minor = 0;
    glGetIntegerv(GL_MAJOR_VERSION, &major);
    glGetIntegerv(GL_MINOR_VERSION, &minor);
    sprintf(SOGL.info.version, "%d.%d", major, minor);

    SOGL.info.renderer = glGetString(GL_RENDERER);
    if (SOGL.info.renderer == NULL) sgLogError("glGetString :: failed to get SGcontext->renderer string");

    SOGL.init = SGTRUE;

    sgInitResourceBlock(SG_MESH);
    sgInitResourceBlock(SG_SHADER);
    sgInitResourceBlock(SG_TEXTURE);

    sgContextDebug(&SOGL);

    #ifdef SG_PRECOMPILE
      const char* sgDefaultVertexShader = 
      "# version 400 core\n"
      "layout (location=0) in vec3 vPos;\n"
      "layout (location=1) in vec2 vTexCoord;\n"
      "out vec2 texCoord;\n"
      "void main() {\n"
      "   gl_Position = vec4(vPos, 1.0);\n"
      "   texCoord = vec2(vTexCoord);\n"
      "}";
      
      const char* sgDefaultFragmentShader = 
      "#version 400 core\n"
      "out vec4 fragColor;\n"
      "in vec2 texCoord;\n"
      "uniform sampler2D fTexture;\n"
      "void main() {\n"
      "   vec4 baseColor = vec4(1.0);\n"
      "   fragColor = texture(fTexture, texCoord) * baseColor;\n"
      "}";

      sgDefaultShader = sgGenHandle(SG_SHADER, sgDefaultVertexShader, sgDefaultFragmentShader, (char*[]) {"model"}, 1);
      sgBindConstructor(&sgDefaultShader);
    #endif
}
