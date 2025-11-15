#include "objects.h"
#include <GL/glut.h>
#include <cmath>
#include "../animations/animations.h"
#include "../textures/textures.h"

ObjectsManager::ObjectsManager(SceneState& state, AnimationsManager* animMgr, TexturesManager* texMgr)
    : sceneState(state), animationsManager(animMgr), texturesManager(texMgr) {}

void ObjectsManager::desenharChao() {
    glBindTexture(GL_TEXTURE_2D, sceneState.floorTextureID);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(0.6f, 0.6f, 0.6f);
    int numQuads = 12; //Min recomendado: 6 
    float size = 10.0f;
    float halfSize = size / 2.0f;
    float step = size / numQuads;
    float texStep = 10.0f / numQuads;
    glBegin(GL_QUADS);
    for (int i = 0; i < numQuads; ++i) {
        for (int j = 0; j < numQuads; ++j) {
            float x0 = -halfSize + i * step;
            float x1 = x0 + step;
            float z0 = -halfSize + j * step;
            float z1 = z0 + step;
            float tx0 = i * texStep;
            float tx1 = tx0 + texStep;
            float tz0 = j * texStep;
            float tz1 = tz0 + texStep;
            glNormal3f(0, 1, 0);
            glTexCoord2f(tx0, tz0); glVertex3f(x0, 0, z0);
            glTexCoord2f(tx1, tz0); glVertex3f(x1, 0, z0);
            glTexCoord2f(tx1, tz1); glVertex3f(x1, 0, z1);
            glTexCoord2f(tx0, tz1); glVertex3f(x0, 0, z1);
        }
    }
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ObjectsManager::desenharCone() {
    glBindTexture(GL_TEXTURE_2D, sceneState.brickTextureID);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f);
    glRotatef(-90, 1, 0, 0);
    // Parâmetros do cone
    float radius = 0.7f;
    float height = 1.0f;
    int slices = 12; //min recomendado: 6
    // Desenha base do cone (círculo)
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, -1);
    glTexCoord2f(0.5f, 0.5f);
    glVertex3f(0, 0, 0);
    for (int i = 0; i <= slices; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(slices);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glTexCoord2f(0.5f + 0.5f * cosf(theta), 0.5f + 0.5f * sinf(theta));
        glVertex3f(x, y, 0);
    }
    glEnd();
    // Desenha lateral do cone
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0, 0, 1);
    glTexCoord2f(0.5f, 1.0f);
    glVertex3f(0, 0, height);
    for (int i = 0; i <= slices; ++i) {
        float theta = 2.0f * 3.1415926f * float(i) / float(slices);
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glTexCoord2f(float(i) / slices, 0.0f);
        glVertex3f(x, y, 0);
    }
    glEnd();
    glPopMatrix();
}

void ObjectsManager::desenharCubo() {
    glColor3f(0.8f, 0.5f, 0.3f); // Marrom
    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void ObjectsManager::desenharBola() {
    if (animationsManager) {
        animationsManager->animarBola();
    }
    glColor3f(1.0f, 0.2f, 0.2f); // Vermelha
    glPushMatrix();
    glTranslatef(sceneState.ball.x, 0.5f, sceneState.ball.z);
    glRotatef(sceneState.ball.rotation, 0, 1, 0);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();
}

void ObjectsManager::desenharPendulo() {
    if (animationsManager)
        animationsManager->animarPendulo();

    // Posição do pivô do pêndulo
    glPushMatrix();
    glTranslatef(sceneState.pendulo.x, 3.0f, sceneState.pendulo.z);
    glRotatef(sceneState.pendulo.rotation, 0, 0, 1); // Rotação em torno do eixo Z
    glColor3fv(sceneState.pendulo.cor);
    glBegin(GL_LINES);
    glVertex3f(0, 0, 0); // Pivô
    glVertex3f(0, -sceneState.pendulo.comprimento, 0); // Fim da haste
    glEnd();
    // Desenha esfera na ponta
    glTranslatef(0, -sceneState.pendulo.comprimento, 0);
    glutSolidSphere(0.2f, 16, 16);
    glPopMatrix();
}