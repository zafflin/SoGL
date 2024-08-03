#define SG_PREGENERATE   // specify the pre-generation of default meshes

#include <sogl.h>

void main() {
    soglInit(); sgInit2D();
    
    SGhandle thandle = sgGenHandle(SG_TEXTURE, "assets\\textures\\brick.jpg", SG_TEX2D_RGB);
    sgBindConstructor(&thandle);
    
    SGhandle shandle = sgGenHandle(SG_SHADER, "assets\\shaders\\default.vert", "assets\\shaders\\default.frag");
    sgBindConstructor(&shandle);

    sgClearColor(25, 60, 80, 255);
    while (!sgShouldQuit(SOGL.resources.window)) {

        glfwPollEvents();

        sgBeginRender(SG_TRIANGLES);
                                    //    no uniform array, so 0 uniforms :)
        sgRender(sgDrawQuad(&thandle, &shandle, NULL, 0));

        sgEndRender(SOGL.resources.window);
    }
}
