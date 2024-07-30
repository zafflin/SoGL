#include <sogl.h>

void main() {
    soglInit();

    f32 qverts[] = {
        0.5f,  0.5f, 0.0f,      // top right
        0.5f, -0.5f, 0.0f,      // bottom right
        -0.5f, -0.5f, 0.0f,     // bottom left
        
        -0.5f, -0.5f, 0.0f,     // bottom left
        -0.5f,  0.5f, 0.0f,     // top left 
        0.5f,  0.5f, 0.0f};      // top right
    
    SGhandle mhandle = sgGenMesh(qverts, sgGetVeretxCount(qverts));
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
