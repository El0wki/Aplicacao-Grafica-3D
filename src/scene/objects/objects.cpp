

#include "objects.h"
#include <GL/glut.h>
#include "../animations/animations.h"
#include "../textures/textures.h"

ObjectsManager::ObjectsManager(SceneState& state, AnimationsManager* animMgr, TexturesManager* texMgr)
    : sceneState(state), animationsManager(animMgr), texturesManager(texMgr) {}

void ObjectsManager::desenharChao() {
    glBindTexture(GL_TEXTURE_2D, sceneState.floorTextureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-10, 0, -10);
    glTexCoord2f(10, 0); glVertex3f( 10, 0, -10);
    glTexCoord2f(10, 10); glVertex3f( 10, 0, 10);
    glTexCoord2f(0, 10); glVertex3f(-10, 0, 10);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

void ObjectsManager::desenharCubo() {
    glColor3f(0.8f, 0.5f, 0.3f); // Marrom
    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

void ObjectsManager::desenharCone() {
    glColor3f(0.6f, 0.2f, 0.2f); 
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); 
    glRotatef(-90, 1, 0, 0); 
    glutSolidCone(0.7, 1.0, 15, 15);
    glPopMatrix();
}

void ObjectsManager::desenharBola() {
    if (animationsManager) {
        animationsManager->animarBola();
    }
    // Se quiser aplicar textura específica, pode chamar aqui
    glColor3f(1.0f, 0.2f, 0.2f); // Vermelha
    glPushMatrix();
    glTranslatef(sceneState.ball.x, 0.5f, sceneState.ball.z);
    glRotatef(sceneState.ball.rotation, 0, 1, 0);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();
}