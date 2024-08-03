#define SG_PRECOMPILE    // specify the pre-compilation of default shaders

#include <sogl.h>

void main() {
    soglInit(); sgInitShapes();

    SGmat4 model = sgIdentity();
    sgSetUniform(&sgDShader2ModelUni, &model);
    sgSendUniform(&sgDShader2ModelUni);

    SGmat4 rotX = sgIdentity();
    SGmat4 rotY = sgIdentity();
    SGmat4 rotZ = sgIdentity();
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

        rotation.x += (50.0f * deltaTime); // 50 degrees per second
        rotation.y += (30.0f * deltaTime); // 30 degrees per second
        rotation.z += (20.0f * deltaTime); // 20 degrees per second

        if (rotation.x >= 360.0f) rotation.x -= 360.0f;
        if (rotation.y >= 360.0f) rotation.y -= 360.0f;
        if (rotation.z >= 360.0f) rotation.z -= 360.0f;

        // dont forget to reset your matrices!
        rotX = sgIdentity();
        rotY = sgIdentity();
        rotZ = sgIdentity();
        model = sgIdentity();

        sgRotXMat4(&rotX, rotation.x * (SG_PI / 180.0f));
        sgRotYMat4(&rotY, rotation.y * (SG_PI / 180.0f));
        sgRotZMat4(&rotZ, rotation.z * (SG_PI / 180.0f));

        sgMulMat4(&model, model, rotX);
        sgMulMat4(&model, model, rotY);
        sgMulMat4(&model, model, rotZ);

        sgSetUniform(&sgDShader2ModelUni, &model);

        sgBeginRender(SG_TRIANGLES);
        
        sgRender(sgDrawTriangle(&thandle, &sgDShader2, (SGhandle[]){sgDShader2ModelUni}, 1));

        sgEndRender(SOGL.resources.window);
    }
}
