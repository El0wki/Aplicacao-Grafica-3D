#include "objects.h"
#include <GL/glut.h>
#include "state.h" 

extern SceneState g_sceneState;

// --- Desenhar chão ---
void desenharChao() {
    glBindTexture(GL_TEXTURE_2D, g_sceneState.floorTextureID);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0); glVertex3f(-10, 0, -10);
    glTexCoord2f(10, 0); glVertex3f( 10, 0, -10);
    glTexCoord2f(10, 10); glVertex3f( 10, 0, 10);
    glTexCoord2f(0, 10); glVertex3f(-10, 0, 10);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
}

// --- Desenhar casa ---
void desenharCubo() {
    glColor3f(0.8f, 0.5f, 0.3f); // Marrom
    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

// --- Desenhar cone ---
void desenharCone() {
    glColor3f(0.6f, 0.2f, 0.2f); 
    glPushMatrix();
    glTranslatef(0.0f, 1.0f, 0.0f); 
    glRotatef(-90, 1, 0, 0); 
    glutSolidCone(0.7, 1.0, 15, 15);
    glPopMatrix();
}

// --- Desenhar bola ---
void desenharBola() {
    glColor3f(1.0f, 0.2f, 0.2f); // Vermelha
    glPushMatrix();
    glTranslatef(g_sceneState.ball.x, 0.5f, g_sceneState.ball.z);
    glRotatef(g_sceneState.ball.rotation, 0, 1, 0);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();
}