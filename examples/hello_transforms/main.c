#define SG_PRECOMPILE    // specify the pre-compilation of default shaders
#define SG_PREGENERATE   // specify the pre-generation of default meshes

#include <sogl.h>

void main() {
    soglInit(); sgInitShapes();

    SGmat4 model = sgIdentity();
    sgSetUniform(&sgDShader2ModelUni, &model);
    sgSendUniform(&sgDShader2ModelUni);

    SGmat4 rotmat = sgIdentity();
    SGvec3 rotation = {0.0f, 0.0f, 0.0f};
    
    SGhandle thandle = sgGenHandle(SG_TEXTURE, "assets\\textures\\brick.jpg", SG_TEX2D_RGB);
    sgBindConstructor(&thandle);

    sgClearColor(25, 60, 80, 255);

    float lastTime = glfwGetTime();
    while (!sgShouldQuit(SOGL.resources.window)) {
        float currentTime = glfwGetTime();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glfwPollEvents();

        rotation.z += (20.0f * deltaTime); // 20 degrees per second
        if (rotation.z >= 360.0f) rotation.z -= 360.0f;

        rotmat = sgIdentity();
        sgRotMat4(&rotmat, rotation.x * (SG_PI / 180.0f), rotation.y * (SG_PI / 180.0f), rotation.z * (SG_PI / 180.0f));
        
        model = sgIdentity();
        sgMulMat4(&model, model, rotmat);

        sgBeginRender(SG_TRIANGLES);
        
        sgRender(sgDrawQuad(&thandle, &sgDShader2, (SGhandle[]){sgDShader2ModelUni}, sgDShader2UniCount));

        sgEndRender(SOGL.resources.window);
    }
}
