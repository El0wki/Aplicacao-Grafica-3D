
#include "controls.h"
#include <GL/glut.h>
#include <cmath>

Controls::Controls(SceneState& state) : sceneState(state) {}

void Controls::toggleAllAnimations() {
    bool newState = !(sceneState.ball.isAnimating || sceneState.pendulo.isAnimating);
    sceneState.ball.isAnimating = newState;
    sceneState.pendulo.isAnimating = newState;
}

void Controls::teclado(unsigned char key, int x, int y) {
    float speed = 0.2f;
    float yawRad = sceneState.camera.yaw * 3.14159f / 180.0f;

    switch (key) {
        case 'w': case 'W':
            sceneState.camera.x += sin(yawRad) * speed;
            sceneState.camera.z -= cos(yawRad) * speed;
            break;
        case 's': case 'S':
            sceneState.camera.x -= sin(yawRad) * speed;
            sceneState.camera.z += cos(yawRad) * speed;
            break;
        case 'a': case 'A': 
            sceneState.camera.x += sin(yawRad - 1.5708f) * speed;
            sceneState.camera.z -= cos(yawRad - 1.5708f) * speed;
            break;
        case 'd': case 'D': 
            sceneState.camera.x += sin(yawRad + 1.5708f) * speed;
            sceneState.camera.z -= cos(yawRad + 1.5708f) * speed;
            break;
        case 'q': case 'Q': sceneState.camera.y += speed; break;
        case 'e': case 'E': sceneState.camera.y -= speed; break;
        case ' ': toggleAllAnimations(); break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void Controls::mouseMove(int x, int y) {
    if (sceneState.window.mouseWarped) {
        sceneState.window.mouseWarped = false;
        return;
    }

    int deltaX = x - sceneState.window.width / 2;
    int deltaY = y - sceneState.window.height / 2;

    if (deltaX != 0 || deltaY != 0) {
        float mouseSensitivity = 0.15f;
        sceneState.camera.yaw += deltaX * mouseSensitivity;
        sceneState.camera.pitch -= deltaY * mouseSensitivity;

        if (sceneState.camera.pitch > 89.0f) sceneState.camera.pitch = 89.0f;
        if (sceneState.camera.pitch < -89.0f) sceneState.camera.pitch = -89.0f;

        sceneState.window.mouseWarped = true; 
        glutWarpPointer(sceneState.window.width / 2, sceneState.window.height / 2); 
        glutPostRedisplay();
    }
}