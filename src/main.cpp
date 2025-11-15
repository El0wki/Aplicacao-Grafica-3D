#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "state.h"
#include "lightning/lights.h"
#include "controls/controls.h"
#include "scene/objects/objects.h"
#include "scene/animations/animations.h"

// Instância global de Controls
Controls* g_controls = nullptr;
#include "scene/textures/textures.h" 
#include "scene/textures/textures.h" 

// Estado Global
SceneState g_sceneState;
LightsManager* g_lightsManager = nullptr;
const std::vector<LightSource>* sceneLights = nullptr;
ObjectsManager* g_objectsManager = nullptr;
TexturesManager* g_texturesManager = nullptr;
AnimationsManager* g_animationsManager = nullptr;

// Funções encaminhadoras para GLUT
void tecladoForward(unsigned char key, int x, int y) {
    if (g_controls) g_controls->teclado(key, x, y);
}

void mouseMoveForward(int x, int y) {
    if (g_controls) g_controls->mouseMove(x, y);
}

void setupLights() {
    glEnable(GL_LIGHTING);
    float amb[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    if (!sceneLights) return;
    for (size_t i = 0; i < sceneLights->size(); ++i) {
        if (i >= 8) break;
        GLenum lightId = GL_LIGHT0 + i;
        glEnable(lightId);
        glLightfv(lightId, GL_POSITION, (*sceneLights)[i].position);
        glLightfv(lightId, GL_DIFFUSE, (*sceneLights)[i].color);

                glLightf(lightId, GL_CONSTANT_ATTENUATION, 0.5f);   // Valor base
        glLightf(lightId, GL_LINEAR_ATTENUATION, 0.1f);     // Atenuação linear
        glLightf(lightId, GL_QUADRATIC_ATTENUATION, 0.05f); // Atenuação quadrática

        // Se usar spotlight:
        glLightfv(lightId, GL_SPOT_DIRECTION, (*sceneLights)[i].spotDirection);
        glLightf(lightId, GL_SPOT_CUTOFF, (*sceneLights)[i].spotCutoff);
    }
}

void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);

    // Inicializa texturas
    if (g_texturesManager) {
        g_texturesManager->gerarTexturaChao();
        g_texturesManager->gerarTexturaTijolo();
        // g_texturesManager->gerarTexturaMadeira();
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)g_sceneState.window.width / (double)g_sceneState.window.height, 0.1, 100.0);
}

// --- Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Aplica a câmera primeiro
    float yawRad = g_sceneState.camera.yaw * 3.14159f / 180.0f;
    float pitchRad = g_sceneState.camera.pitch * 3.14159f / 180.0f;
    float lx = cos(pitchRad) * sin(yawRad);
    float ly = sin(pitchRad);
    float lz = cos(pitchRad) * -cos(yawRad);
    gluLookAt(g_sceneState.camera.x, g_sceneState.camera.y, g_sceneState.camera.z,
              g_sceneState.camera.x + lx, g_sceneState.camera.y + ly, g_sceneState.camera.z + lz,
              0, 1, 0);

    // Agora configura luzes (depois da câmera)
    setupLights();

    // Desenha todos os objetos da cena
    if (g_objectsManager) {
        g_objectsManager->desenharChao();
        g_objectsManager->desenharCone();
        g_objectsManager->desenharCubo();
        g_objectsManager->desenharBola();
        g_objectsManager->desenharPendulo();
        // g_objectsManager->desenharCaixaMadeira();
    }

    glutSwapBuffers();
}

// --- Animação ---
void timer(int v) {
    // Animações e texturas são delegadas ao ObjectsManager
    glutTimerFunc(16, timer, 0);
    glutPostRedisplay();
}

// --- Main ---
int main(int argc, char** argv) {
    g_lightsManager = new LightsManager();
    sceneLights = &g_lightsManager->getLights();
    g_controls = new Controls(g_sceneState);
    g_animationsManager = new AnimationsManager(g_sceneState);
    g_texturesManager = new TexturesManager(g_sceneState);
    g_objectsManager = new ObjectsManager(g_sceneState, g_animationsManager, g_texturesManager);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(g_sceneState.window.width, g_sceneState.window.height);
    glutCreateWindow("Cena 3D");
    glutDisplayFunc(display);
    glutKeyboardFunc(tecladoForward);
    glutPassiveMotionFunc(mouseMoveForward);
    glutSetCursor(GLUT_CURSOR_NONE);  
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    delete g_controls;
    delete g_lightsManager;
    delete g_objectsManager;
    delete g_texturesManager;
    delete g_animationsManager;
    return 0;
}