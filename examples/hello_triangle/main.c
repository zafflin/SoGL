#include <sogl.h>

void main() {
    soglInit(); sgInit2D();

    SGhandle shandle = sgGenShader("assets\\shaders\\default.vert", "assets\\shaders\\default.frag");
    sgBindConstructor(&shandle);

    sgClearColor(25, 60, 80, 255);
    while (!sgShouldQuit(SOGL.resources.window)) {
        glfwPollEvents();
        sgBeginRender(SG_TRIANGLES);
        sgRender(sgDrawTriangle(&shandle));
        sgEndRender(SOGL.resources.window);
    }
}
