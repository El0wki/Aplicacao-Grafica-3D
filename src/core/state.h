#ifndef STATE_H
#define STATE_H

#include <GL/glut.h>

// --- Estruturas de Dados da Cena ---

struct Camera {
    float x = 0.0f, y = 1.6f, z = 5.0f;
    float yaw = 0.0f, pitch = 0.0f;
};

struct Ball {
    float x = -2.0f, z = 0.0f, rotation = 0.0f;
    bool isAnimating = true;
};

struct Window {
    int width = 1280;
    int height = 720; // Corrigido o valor da altura
    bool mouseWarped = false;
};

struct LightSource {
    float position[4];
    float color[4];
    // Propriedades para spotlight (opcional)
    float spotDirection[3] = {0.0f, -1.0f, 0.0f};
    float spotCutoff = 180.0f; // 180 desativa o efeito de cone
};

// --- Estado Global da Cena ---

struct SceneState {
    Camera camera;
    Ball ball;
    Window window;

    // IDs das texturas
    GLuint floorTextureID;
    GLuint brickTextureID;
    GLuint woodTextureID;
};

// Declaração da variável global que será definida em main.cpp
extern SceneState g_sceneState;

#endif // STATE_H