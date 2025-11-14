//Exemplo gerado pelo Grok com algumas modificações
//main.cpp
#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <vector>
#include "lights.h" // Inclui as declarações de 'lights.h'

// O vetor de luzes da cena, agora preenchido por uma função externa.
std::vector<LightSource> sceneLights;

// --- Variáveis da câmera ---
float camX = 0.0f, camY = 2.0f, camZ = 8.0f; // Posição
float camYaw = 0.0f; // Rotação horizontal
float camPitch = 0.0f; // Rotação vertical

// --- Variáveis do Mouse e Janela ---
int windowWidth = 800;
int windowHeight = 600;
bool mouseWarped = false; // Flag para controlar o cursor

// --- Bola ---
bool animarBola = false; 
float bolaX = -2.0f, bolaZ = 0.0f, bolaRot = 0.0f; 

// --- ID da textura procedural ---
GLuint texturaChao; //Id da textura do chão

// --- Gerar textura procedural (grama quadriculada) ---
void gerarTexturaChao() {
    const int TAM = 64; // 64x64 pixels
    unsigned char* data = new unsigned char[TAM * TAM * 3];
    for (int y = 0; y < TAM; ++y) {
        for (int x = 0; x < TAM; ++x) {
            int idx = (y * TAM + x) * 3;
            // Padrão quadriculado verde (grama)
            bool verdeEscuro = ((x / 8) % 2) == ((y / 8) % 2);
            unsigned char r = 0;
            unsigned char g = verdeEscuro ? 30 : 70;
            unsigned char b = 0;
            data[idx + 0] = r;
            data[idx + 1] = g;
            data[idx + 2] = b;
        }
    }
    glGenTextures(1, &texturaChao);
    glBindTexture(GL_TEXTURE_2D, texturaChao);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TAM, TAM, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void setupLights() {
    // Habilita a iluminação e define a luz ambiente global
    glEnable(GL_LIGHTING);
    float amb[] = {0.3f, 0.3f, 0.3f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);

    // Percorre o vetor de luzes e configura cada uma
    for (size_t i = 0; i < sceneLights.size(); ++i) {
        // O OpenGL tem um limite de luzes (geralmente 8), GL_LIGHT0 a GL_LIGHT7
        if (i >= 8) break; 

        GLenum lightId = GL_LIGHT0 + i; // Calcula o ID da luz (GL_LIGHT0, GL_LIGHT1, etc.)
        
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

    // Chama a nova função para configurar a iluminação
    setupLights();
    
    // Gerar textura procedural
    gerarTexturaChao();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)windowWidth / (double)windowHeight, 0.1, 100.0);
}

// --- Desenhar chão ---
void desenharChao() {
    glBindTexture(GL_TEXTURE_2D, texturaChao);
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
void desenharCasa() {
    glColor3f(0.8f, 0.5f, 0.3f); // Marrom
    glPushMatrix();
    glTranslatef(0, 0.5f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();
}

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
    glTranslatef(bolaX, 0.5f, bolaZ);
    glRotatef(bolaRot, 0, 1, 0);
    glutSolidSphere(0.5f, 20, 20);
    glPopMatrix();
}

// --- Desenhar Mira (Crosshair) ---
void desenharMira() {
    // Salva as configurações atuais de matriz e atributos
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, windowWidth, 0, windowHeight); // Projeção 2D

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    // Desabilita iluminação e profundidade para desenhar a mira em 2D
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);

    glColor3f(1.0f, 1.0f, 1.0f); // Cor branca
    glLineWidth(2.0f); // Linha um pouco mais grossa

    // Desenha uma cruz no centro da tela
    glBegin(GL_LINES);
    // Linha horizontal
    glVertex2i(windowWidth / 2 - 10, windowHeight / 2);
    glVertex2i(windowWidth / 2 + 10, windowHeight / 2);
    // Linha vertical
    glVertex2i(windowWidth / 2, windowHeight / 2 - 10);
    glVertex2i(windowWidth / 2, windowHeight / 2 + 10);
    glEnd();

    // Restaura as configurações que foram desabilitadas
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);

    // Restaura as matrizes originais
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

// --- Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Câmera FPS com Yaw (horizontal) e Pitch (vertical)
    float yawRad = camYaw * 3.14159f / 180.0f;
    float pitchRad = camPitch * 3.14159f / 180.0f;

    float lx = cos(pitchRad) * sin(yawRad);
    float ly = sin(pitchRad);
    float lz = cos(pitchRad) * -cos(yawRad);

    gluLookAt(camX, camY, camZ,
              camX + lx, camY + ly, camZ + lz,
              0, 1, 0);

    desenharChao();
    desenharCone();
    desenharCasa();
    desenharBola();

    // Desenha a mira por último para que ela fique sobre a cena 3D
    desenharMira();

    glutSwapBuffers();
}

// --- Teclado ---
void teclado(unsigned char key, int x, int y) {
    float speed = 0.2f;
    float yawRad = camYaw * 3.14159f / 180.0f;

    switch (key) {
        case 'w': case 'W':
            camX += sin(yawRad) * speed;
            camZ -= cos(yawRad) * speed;
            break;
        case 's': case 'S':
            camX -= sin(yawRad) * speed;
            camZ += cos(yawRad) * speed;
            break;
        // Movimento lateral (strafe)
        case 'a': case 'A': 
            camX += sin(yawRad - 1.5708f) * speed; // 90 graus à esquerda
            camZ -= cos(yawRad - 1.5708f) * speed;
            break;
        case 'd': case 'D': 
            camX += sin(yawRad + 1.5708f) * speed; // 90 graus à direita
            camZ -= cos(yawRad + 1.5708f) * speed;
            break;
        case 'q': case 'Q': camY += speed; break;
        case 'e': case 'E': camY -= speed; break;
        case ' ': animarBola = !animarBola; break;
        case 27: exit(0); break;
    }
    glutPostRedisplay();
}

// --- Movimento do Mouse ---
void mouseMove(int x, int y) {
    if (mouseWarped) {
        mouseWarped = false;
        return;
    }

    int deltaX = x - windowWidth / 2;
    int deltaY = y - windowHeight / 2;

    if (deltaX != 0 || deltaY != 0) {
        float mouseSensitivity = 0.15f;
        camYaw += deltaX * mouseSensitivity;
        camPitch -= deltaY * mouseSensitivity;

        if (camPitch > 89.0f) camPitch = 89.0f;
        if (camPitch < -89.0f) camPitch = -89.0f;

        mouseWarped = true; 
        glutWarpPointer(windowWidth / 2, windowHeight / 2); 
        glutPostRedisplay();
    }
}

// --- Animação ---
void timer(int v) {
    if (animarBola) {
        bolaZ += 0.03f;
        bolaRot += 10.0f;
        if (bolaZ > 2.0f) {
            bolaZ = -2.0f;
            bolaRot = 0;
        }
    }
    glutTimerFunc(16, timer, 0);
    glutPostRedisplay();
}

// --- Main ---
int main(int argc, char** argv) {
    // Preenche o vetor global de luzes chamando a função externa
    sceneLights = createSceneLights();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cena 3D - Textura Procedural");
    glutDisplayFunc(display);
    glutKeyboardFunc(teclado);
    glutPassiveMotionFunc(mouseMove); 
    glutSetCursor(GLUT_CURSOR_NONE);  
    glutTimerFunc(0, timer, 0);
    init();
    glutMainLoop();
    return 0;
}