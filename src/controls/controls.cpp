#include "controls.h"
#include <GL/glut.h>
#include <cmath>
#include "state.h" 

extern SceneState g_sceneState;

// --- Teclado ---
void teclado(unsigned char key, int x, int y) {
    float speed = 0.2f;
    float yawRad = g_sceneState.camera.yaw * 3.14159f / 180.0f;

    switch (key) {
        case 'w': case 'W':
            g_sceneState.camera.x += sin(yawRad) * speed;
            g_sceneState.camera.z -= cos(yawRad) * speed;
            break;
        case 's': case 'S':
            g_sceneState.camera.x -= sin(yawRad) * speed;
            g_sceneState.camera.z += cos(yawRad) * speed;
            break;
        case 'a': case 'A': 
            g_sceneState.camera.x += sin(yawRad - 1.5708f) * speed;
            g_sceneState.camera.z -= cos(yawRad - 1.5708f) * speed;
            break;
        case 'd': case 'D': 
            g_sceneState.camera.x += sin(yawRad + 1.5708f) * speed;
            g_sceneState.camera.z -= cos(yawRad + 1.5708f) * speed;
            break;
        case 'q': case 'Q': g_sceneState.camera.y += speed; break;
        case 'e': case 'E': g_sceneState.camera.y -= speed; break;
        case ' ': g_sceneState.ball.isAnimating = !g_sceneState.ball.isAnimating; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

// --- Movimento do Mouse ---
void mouseMove(int x, int y) {
    if (g_sceneState.window.mouseWarped) {
        g_sceneState.window.mouseWarped = false;
        return;
    }

    int deltaX = x - g_sceneState.window.width / 2;
    int deltaY = y - g_sceneState.window.height / 2;

    if (deltaX != 0 || deltaY != 0) {
        float mouseSensitivity = 0.15f;
        g_sceneState.camera.yaw += deltaX * mouseSensitivity;
        g_sceneState.camera.pitch -= deltaY * mouseSensitivity;

        if (g_sceneState.camera.pitch > 89.0f) g_sceneState.camera.pitch = 89.0f;
        if (g_sceneState.camera.pitch < -89.0f) g_sceneState.camera.pitch = -89.0f;

        g_sceneState.window.mouseWarped = true; 
        glutWarpPointer(g_sceneState.window.width / 2, g_sceneState.window.height / 2); 
        glutPostRedisplay();
    }
}