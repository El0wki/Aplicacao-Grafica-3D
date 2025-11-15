#include "textures.h"
#include <GL/glut.h>
#include "state.h"

// Acessa o estado global para armazenar os IDs das texturas
extern SceneState g_sceneState;

// --- Gerar textura procedural (grama quadriculada) ---
void gerarTexturaChao() {
    const int TAM = 64; // 64x64 pixels
    unsigned char* data = new unsigned char[TAM * TAM * 3];
    for (int y = 0; y < TAM; ++y) {
        for (int x = 0; x < TAM; ++x) {
            int idx = (y * TAM + x) * 3;
            bool verdeEscuro = ((x / 8) % 2) == ((y / 8) % 2);
            data[idx + 0] = 0;
            data[idx + 1] = verdeEscuro ? 30 : 70;
            data[idx + 2] = 0;
        }
    }
    glGenTextures(1, &g_sceneState.floorTextureID);
    glBindTexture(GL_TEXTURE_2D, g_sceneState.floorTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TAM, TAM, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

// --- Gerar textura procedural (tijolos) ---
void gerarTexturaTijolo() {
    const int TAM = 64;
    unsigned char* data = new unsigned char[TAM * TAM * 3];
    const int LARGURA_TIJOLO = 16;
    const int ALTURA_TIJOLO = 8;

    for (int y = 0; y < TAM; ++y) {
        for (int x = 0; x < TAM; ++x) {
            int idx = (y * TAM + x) * 3;
            int linha = y / ALTURA_TIJOLO;
            int coluna = x;
            if (linha % 2 == 1) {
                coluna += LARGURA_TIJOLO / 2; // Desloca tijolos em linhas ímpares
            }

            // Define a cor do rejunte
            unsigned char r = 180, g = 180, b = 180;

            // Se não for rejunte, define a cor do tijolo
            if ((y % ALTURA_TIJOLO > 1) && (coluna % LARGURA_TIJOLO > 1)) {
                r = 150 + (x % 10 - y % 10);
                g = 70;
                b = 50;
            }
            data[idx + 0] = r;
            data[idx + 1] = g;
            data[idx + 2] = b;
        }
    }
    glGenTextures(1, &g_sceneState.brickTextureID);
    glBindTexture(GL_TEXTURE_2D, g_sceneState.brickTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TAM, TAM, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
}