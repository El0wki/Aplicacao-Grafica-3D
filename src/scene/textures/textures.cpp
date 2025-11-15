
#include "textures.h"
#include <GL/glut.h>

TexturesManager::TexturesManager(SceneState& state) : sceneState(state) {}

void TexturesManager::gerarTexturaChao() {
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
    glGenTextures(1, &sceneState.floorTextureID);
    glBindTexture(GL_TEXTURE_2D, sceneState.floorTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TAM, TAM, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    delete[] data;
}

void TexturesManager::gerarTexturaTijolo() {
    const int TAM = 64;
    unsigned char* data = new unsigned char[TAM * TAM * 3];
    const int LARGURA_TIJOLO = 16;
    const int ALTURA_TIJOLO = 8;
    for (int y = 0; y < TAM; ++y) {
        for (int x = 0; x < TAM; ++x) {
            int idx = (y * TAM + x) * 3;
            // Calcula linha e coluna do tijolo
            int linha = y / ALTURA_TIJOLO;
            int coluna = x;
            // Linhas ímpares deslocam meio tijolo
            if (linha % 2 == 1) coluna += LARGURA_TIJOLO / 2;
            // Rejunte: borda do tijolo
            bool rejunte = (y % ALTURA_TIJOLO < 2) || (coluna % LARGURA_TIJOLO < 2);
            if (rejunte) {
                // Rejunte cinza claro
                data[idx + 0] = 200;
                data[idx + 1] = 200;
                data[idx + 2] = 200;
            } else {
                // Tijolo vermelho
                data[idx + 0] = 180 + (x % 8);
                data[idx + 1] = 60 + (y % 8);
                data[idx + 2] = 40;
            }
        }
    }
    glGenTextures(1, &sceneState.brickTextureID);
    glBindTexture(GL_TEXTURE_2D, sceneState.brickTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, TAM, TAM, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    delete[] data;
}