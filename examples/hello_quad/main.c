#define SG_PRECOMPILE    // specify the pre-compilation of default shaders
#define SG_PREGENERATE   // specify the pre-generation of default meshes

#include <sogl.h>

void main() {
    soglInit(); sgInit2D();
    
    SGhandle thandle = sgGenHandle(SG_TEXTURE, "assets\\textures\\brick.jpg", SG_TEX2D_RGB);
    sgBindConstructor(&thandle);

    sgClearColor(25, 60, 80, 255);
    while (!sgShouldQuit(SOGL.resources.window)) {
        glfwPollEvents();
        
        sgBeginRender(SG_TRIANGLES);
        
        sgRender(sgDrawQuad(&sgDefaultShader, &thandle));

        sgEndRender(SOGL.resources.window);
    }
}
