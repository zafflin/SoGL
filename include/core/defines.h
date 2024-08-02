#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#define sgValidatePtr(ptr) (ptr==NULL) ? 0 : 1

// Unsigned int types.
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

// Signed int types.
typedef signed char i8;
typedef signed short i16;
typedef signed int i32;
typedef signed long long i64;

// Floating point types
typedef float f32;
typedef double f64;

// Boolean types
typedef int b32;
typedef char b8;

typedef struct SGcontext SGcontext;

// Dynamic vertex buffers (position + texcoords + colors + indices arrays)
typedef struct SGvertexbuffer {
    unsigned int vao;           // OpenGL Vertex Array Object id
    unsigned int vbo[4];           // OpenGL Vertex Buffer Objects id (4 types of vertex data [position, texture, color, normal])
    unsigned int nverts;                 // Number of vertices in the buffer
} SGvertexbuffer;

typedef struct SGuniform {
    char* name;
    void* data;
    unsigned int type;      // SoGL uniform type ( SG_UNI_MAT4, SG_UNI_VEC2/3/4, etc.. )
    unsigned int location;
} SGuniform;

typedef struct SGshader {
    u32 program;
    SGuniform uniforms[16];     // 16 uniforms per shader :)
} SGshader;

typedef struct SGtexture2D {
    unsigned int width;
    unsigned int height;
    unsigned int glref;        // OpenGL context ID
    unsigned char* raw;      // raw image data
    unsigned int nchannels;     // number of color channels (e.g. RGB(3), RGBA(4))
} SGtexture2D;

// Resource Types
#define SG_RESOURCE_TYPES 3     // global count of resource types (mainly for generation count)
typedef enum ResourceType {
    SG_MESH=0,
    SG_SHADER,
    SG_TEXTURE
} ResourceType;

typedef enum SGhandletype {
    SG_SHADER_MAX=1000,
    SG_MESH_MAX=100000,
    SG_TEXTURE_MAX=100000
} SGhandletype;

// Unified Handle Structure
typedef struct SGhandle {
    void* config; // Points to type-specific configuration data
    unsigned int id;
    unsigned int err;
    ResourceType type;
    unsigned char enabled;  // flag to track when a resource is enabled in the helix machine
} SGhandle;

// Configuration Data Structures
typedef struct SGtexconfig {
    char* src;
   unsigned int format;
   SGtexture2D texture2D;
} SGtexconfig;

typedef struct SGshaderconfig {
    SGshader shader;
    char** uniforms;
    unsigned int nuniforms;
    const char* vertexShaderSource;
    const char* fragmentShaderSource;
} SGshaderconfig;

typedef struct SGmeshconfig {
    float* verts;  // temporary copy of vertices to pass along to the Constructor Context
    float* texcoords;  // temporary copy of vertices to pass along to the Constructor Context
    unsigned int nvertices;
    unsigned int ntexcoords;
    SGvertexbuffer vbuffer;
} SGmeshconfig;

void sgGetHandleStr(const SGhandle* handle, char* str) {
    if (handle->type == SG_MESH) sprintf(str, "SG_MESH");
    else if (handle->type == SG_SHADER) sprintf(str, "SG_SHADER");
    else if (handle->type == SG_TEXTURE) sprintf(str, "SG_TEXTURE");
}

void sgBindGenerator(SGhandle* target);
void sgUnbindGenerator(void);
SGhandle sgGenHandle(u32 htype, ...);
SGhandle sgGenTexture(va_list args);
SGhandle sgGenShader(va_list args);
SGhandle sgGenMesh(va_list args);

void* sgBindConstructor(SGhandle* target);
void sgUnbindConstructor(void);
void sgConstTexture(void);
void sgConstShader(void);
void sgConstMesh(void);

void sgBindStore(SGhandle* target);
void sgUnbindStore(void);
void sgInitResourceBlock(ResourceType type);
void sgStoreMesh(SGhandle* handle);
void sgStoreShader(SGhandle* handle);
void sgStoreTexture(SGhandle* handle);

typedef struct SGdrawcall {
    SGshader shader;
    unsigned int err;
    unsigned int vao;
    unsigned int texID;
    unsigned int nvertices;
} SGdrawcall;
void sgGetRenderModeStr(char* str);
void sgBeginRender(u32 mode);
SGdrawcall* sgDrawCall(const SGhandle* mhandle, const SGhandle* shandle, const SGhandle* thandle);
void sgRender(SGdrawcall* call);
void sgUnbindRender(void);
void sgEndRender(void* window);

#define SGTRUE 1
#define SGFALSE 0

#define SG_KEY_SPACE              32
#define SG_KEY_APOSTROPHE         39  /* ' */
#define SG_KEY_COMMA              44  /* , */
#define SG_KEY_MINUS              45  /* - */
#define SG_KEY_PERIOD             46  /* . */
#define SG_KEY_SLASH              47  /* / */
#define SG_KEY_0                  48
#define SG_KEY_1                  49
#define SG_KEY_2                  50
#define SG_KEY_3                  51
#define SG_KEY_4                  52
#define SG_KEY_5                  53
#define SG_KEY_6                  54
#define SG_KEY_7                  55
#define SG_KEY_8                  56
#define SG_KEY_9                  57
#define SG_KEY_SEMICOLON          59  /* ; */
#define SG_KEY_EQUAL              61  /* = */
#define SG_KEY_A                  65
#define SG_KEY_B                  66
#define SG_KEY_C                  67
#define SG_KEY_D                  68
#define SG_KEY_E                  69
#define SG_KEY_F                  70
#define SG_KEY_G                  71
#define SG_KEY_H                  72
#define SG_KEY_I                  73
#define SG_KEY_J                  74
#define SG_KEY_K                  75
#define SG_KEY_L                  76
#define SG_KEY_M                  77
#define SG_KEY_N                  78
#define SG_KEY_O                  79
#define SG_KEY_P                  80
#define SG_KEY_Q                  81
#define SG_KEY_R                  82
#define SG_KEY_S                  83
#define SG_KEY_T                  84
#define SG_KEY_U                  85
#define SG_KEY_V                  86
#define SG_KEY_W                  87
#define SG_KEY_X                  88
#define SG_KEY_Y                  89
#define SG_KEY_Z                  90
#define SG_KEY_LEFT_BRACKET       91  /* [ */
#define SG_KEY_BACKSLASH          92  /* \ */
#define SG_KEY_RIGHT_BRACKET      93  /* ] */
#define SG_KEY_GRAVE_ACCENT       96  /* ` */
#define SG_KEY_WORLD_1            161 /* non-US #1 */
#define SG_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define SG_KEY_ESCAPE             256
#define SG_KEY_ENTER              257
#define SG_KEY_TAB                258
#define SG_KEY_BACKSPACE          259
#define SG_KEY_INSERT             260
#define SG_KEY_DELETE             261
#define SG_KEY_RIGHT              262
#define SG_KEY_LEFT               263
#define SG_KEY_DOWN               264
#define SG_KEY_UP                 265
#define SG_KEY_PAGE_UP            266
#define SG_KEY_PAGE_DOWN          267
#define SG_KEY_HOME               268
#define SG_KEY_END                269
#define SG_KEY_CAPS_LOCK          280
#define SG_KEY_SCROLL_LOCK        281
#define SG_KEY_NUM_LOCK           282
#define SG_KEY_PRINT_SCREEN       283
#define SG_KEY_PAUSE              284
#define SG_KEY_F1                 290
#define SG_KEY_F2                 291
#define SG_KEY_F3                 292
#define SG_KEY_F4                 293
#define SG_KEY_F5                 294
#define SG_KEY_F6                 295
#define SG_KEY_F7                 296
#define SG_KEY_F8                 297
#define SG_KEY_F9                 298
#define SG_KEY_F10                299
#define SG_KEY_F11                300
#define SG_KEY_F12                301
#define SG_KEY_F13                302
#define SG_KEY_F14                303
#define SG_KEY_F15                304
#define SG_KEY_F16                305
#define SG_KEY_F17                306
#define SG_KEY_F18                307
#define SG_KEY_F19                308
#define SG_KEY_F20                309
#define SG_KEY_F21                310
#define SG_KEY_F22                311
#define SG_KEY_F23                312
#define SG_KEY_F24                313
#define SG_KEY_F25                314
#define SG_KEY_NUM_0               320
#define SG_KEY_NUM_1               321
#define SG_KEY_NUM_2               322
#define SG_KEY_NUM_3               323
#define SG_KEY_NUM_4               324
#define SG_KEY_NUM_5               325
#define SG_KEY_NUM_6               326
#define SG_KEY_NUM_7               327
#define SG_KEY_NUM_8               328
#define SG_KEY_NUM_9               329
#define SG_KEY_NUM_DECIMAL         330
#define SG_KEY_NUM_DIVIDE          331
#define SG_KEY_NUM_MULTIPLY        332
#define SG_KEY_NUM_SUBTRACT        333
#define SG_KEY_NUM_ADD             334
#define SG_KEY_NUM_ENTER           335
#define SG_KEY_NUM_EQUAL           336
#define SG_KEY_LEFT_SHIFT         340
#define SG_KEY_LEFT_CONTROL       341
#define SG_KEY_LEFT_ALT           342
#define SG_KEY_LEFT_SUPER         343
#define SG_KEY_RIGHT_SHIFT        344
#define SG_KEY_RIGHT_CONTROL      345
#define SG_KEY_RIGHT_ALT          346
#define SG_KEY_RIGHT_SUPER        347
#define SG_KEY_MENU               348

#ifdef SGEXPORT
#define SGAPI __declspec(dllexport)
#else
#define SGAPI __declspec(dllimport)
#endif

// Platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) 
#define SGPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define SGPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define SGPLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define SGPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define SGPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define SGPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define SGPLATFORM_IOS 1
#define SGPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define SGPLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif
