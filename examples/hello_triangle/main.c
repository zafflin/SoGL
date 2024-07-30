#include <sogl.h>

void main() {
    soglInit();
    
    f32 tverts[] = {
        0.0f,  0.5f, 0.0f,      // top
        0.5f, -0.5f, 0.0f,      // bottom right
        -0.5f, -0.5f, 0.0f};     // bottom left

    SGhandle mhandle = sgGenMesh(tverts, sgGetVeretxCount(tverts));
    SGhandle shandle = sgGenShader("assets\\shaders\\default.vert", "assets\\shaders\\default.frag");
    sgBindConstructor(&mhandle);
    sgBindConstructor(&shandle);

    sgClearColor(25, 60, 80, 255);
    while (!sgShouldQuit(SOGL.resources.window)) {
        glfwPollEvents();
        sgBeginRender(SG_TRIANGLES);
        sgRender(sgDrawCall(mhandle, shandle));
        sgEndRender(SOGL.resources.window);
    }
}
