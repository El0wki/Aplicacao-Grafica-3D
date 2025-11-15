#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>

#include "state.h"
#include "lightning/lights.h"
#include "objects/objects.h"
#include "controls/controls.h"
#include "textures/textures.h" // Inclui o novo cabeçalho de texturas

// Estado Global
SceneState g_sceneState;
std::vector<LightSource> sceneLights;

// A função gerarTexturaChao() foi removida daqui e movida para textures.cpp

void setupLights() {
    glEnable(GL_LIGHTING);
    float amb[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
    for (size_t i = 0; i < sceneLights.size(); ++i) {
        if (i >= 8) break; 
        GLenum lightId = GL_LIGHT0 + i;
        glEnable(lightId);
        glLightfv(lightId, GL_POSITION, sceneLights[i].position);
        glLightfv(lightId, GL_DIFFUSE, sceneLights[i].color);
    }
}

// --- Init ---
void init() {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
    
    // Inicializa luzes e texturas
    sceneLights = createSceneLights(); 
    setupLights();
    gerarTexturaChao();
    gerarTexturaTijolo();
    // gerarTexturaMadeira(); 

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)g_sceneState.window.width / (double)g_sceneState.window.height, 0.1, 100.0);
}

// --- Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float yawRad = g_sceneState.camera.yaw * 3.14159f / 180.0f;
    float pitchRad = g_sceneState.camera.pitch * 3.14159f / 180.0f;
    float lx = cos(pitchRad) * sin(yawRad);
    float ly = sin(pitchRad);
    float lz = cos(pitchRad) * -cos(yawRad);
    gluLookAt(g_sceneState.camera.x, g_sceneState.camera.y, g_sceneState.camera.z,
              g_sceneState.camera.x + lx, g_sceneState.camera.y + ly, g_sceneState.camera.z + lz,
              0, 1, 0);

    // Desenha todos os objetos da cena
    desenharChao();
    desenharCone();
    desenharCubo();
    desenharBola();
    // desenharCaixaMadeira();

    glutSwapBuffers();
}

// --- Animação ---
void timer(int v) {
    if (g_sceneState.ball.isAnimating) {
        g_sceneState.ball.z += 0.03f;
        g_sceneState.ball.rotation += 10.0f;
        if (g_sceneState.ball.z > 2.0f) {
            g_sceneState.ball.z = -2.0f;
            g_sceneState.ball.rotation = 0;
        }
    }
    glutTimerFunc(16, timer, 0);
    glutPostRedisplay();
}

// --- Main ---
int main(int argc, char** argv) {
    sceneLights = createSceneLights();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(g_sceneState.window.width, g_sceneState.window.height);
    glutCreateWindow("Cena 3D");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(mouseMove);
    glutSetCursor(GLUT_CURSOR_NONE);  
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}