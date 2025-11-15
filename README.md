# Aplicação Gráfica 3D com OpenGL

Este projeto demonstra a criação de uma cena 3D interativa utilizando C++ com as bibliotecas OpenGL e FreeGLUT. O código foi estruturado de forma modular para separar responsabilidades e facilitar a manutenção.

A execução pode ser feita de duas maneiras: compilando nativamente no Windows para máxima performance, ou utilizando Docker com WSLg para um ambiente containerizado e de alta performance.

## Funcionalidades

- **Cena 3D:** Renderização de objetos primitivos (chão, cubo, cone, esfera).
- **Estrutura Modular:** Código-fonte organizado em `core`, `controls`, `lightning` e `objects`.
- **Textura Procedural:** O chão da cena utiliza uma textura quadriculada gerada em tempo de execução.
- **Controle de Câmera FPS:** Controle de câmera em primeira pessoa com movimentação pelo teclado e rotação pelo mouse.
- **Iluminação:** Sistema de iluminação com uma luz direcional (sol) e luz ambiente.
- **Animação:** Animação de uma esfera que pode ser iniciada e parada pelo usuário.

---

## Como Executar

Existem dois métodos principais para rodar a aplicação. O método nativo é mais simples se você já tem um ambiente de desenvolvimento C++, enquanto o método Docker garante um ambiente consistente em qualquer máquina com Windows 11.

### Método 1: Compilando Nativo no Windows (Máxima Performance)

Este método oferece a melhor performance gráfica, pois executa o código diretamente no hardware.

#### 1. Instale o Ambiente de Compilação (MSYS2)

1.  **Baixe e Instale o MSYS2:** Acesse [msys2.org](https://www.msys2.org/) e instale a ferramenta.
2.  **Abra o terminal MSYS2 UCRT64** (importante usar esta versão, encontrada no Menu Iniciar) e atualize os pacotes:
    ```bash
    pacman -Syu
    ```
    Pode ser necessário fechar e reabrir o terminal para completar a atualização. Execute o comando novamente se solicitado.
3.  **Instale as ferramentas de compilação e o FreeGLUT:**
    ```bash
    pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-freeglut
    ```

#### 2. Compile e Execute o Projeto

1.  **Navegue até a pasta do projeto** no terminal MSYS2 UCRT64:
    ```bash
    # Exemplo de caminho, ajuste para o seu caso
    cd /c/Users/rafae/Github/Classificadores/Aplicacao-Grafica-3D/src
    ```
2.  **Compile o código:**
    ```bash
    g++ main.cpp lightning/lights.cpp objects/objects.cpp controls/controls.cpp -o aplicacao.exe -Icore -Ilightning -Iobjects -Icontrols -lfreeglut -lopengl32 -lglu32
    ```
3.  **Execute a aplicação:**
    ```bash
    ./aplicacao.exe
    ```

---

### Método 2: Usando Docker com WSLg (Alta Performance e Containerizado)

Este método usa a tecnologia WSLg do Windows 11 para rodar a aplicação gráfica dentro de um contêiner Docker com aceleração de hardware, garantindo um ambiente consistente e de alta performance.

#### 1. Configuração do Ambiente (Passo Único)

1.  **Instale o WSL e o Ubuntu:**

    - Abra a **Microsoft Store**, procure por **"Ubuntu 22.04 LTS"** e instale.
    - Abra o aplicativo Ubuntu pelo Menu Iniciar. Na primeira execução, ele pedirá para você criar um **nome de usuário** e uma **senha**. Guarde essas informações.

2.  **Verifique a Aceleração Gráfica:**
    - Abra o terminal do **Ubuntu** (pelo Menu Iniciar ou digitando `wsl` no PowerShell).
    - Instale as ferramentas gráficas:
      ```bash
      sudo apt-get update
      sudo apt-get install mesa-utils
      ```
    - Verifique se sua GPU está sendo reconhecida:
      ```bash
      glxinfo | grep "OpenGL renderer"
      ```
    - A saída deve mostrar o nome da sua placa de vídeo (ex: NVIDIA, AMD, Intel). Se mostrar, a aceleração está funcionando.

#### 2. Compile e Execute com Docker

1.  **Abra o terminal do Ubuntu** (digitando `wsl` no PowerShell ou abrindo o app Ubuntu).

2.  **Navegue até a pasta raiz do projeto** (a que contém o `Dockerfile`):

    ```bash
    # Exemplo de caminho, ajuste para o seu caso
    cd /mnt/c/Users/rafae/Github/Classificadores/Aplicacao-Grafica-3D
    ```

3.  **Construa a Imagem Docker:**

    ```bash
    docker build -t app-grafica .
    ```

4.  **Execute o Contêiner:**
    ```bash
    docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix app-grafica
    ```
    A janela da aplicação deve abrir, rodando de forma fluida.

---

## Controles

- **W / S**: Mover para frente / trás.
- **A / D**: Mover para os lados (strafe).
- **Mouse**: Controlar a direção da câmera (olhar para cima, baixo, lados).
- **Q / E**: Mover a câmera para cima / baixo.
- **Barra de Espaço**: Iniciar / Parar a animação da bola.
- **ESC**: Fechar a aplicação.

## Estrutura do Projeto

- `src/`: Contém todo o código-fonte da aplicação, dividido em módulos:
  - `main.cpp`: Ponto de entrada da aplicação, responsável pelo loop principal e inicialização.
  - `core/`: Define as estruturas de dados centrais, como o estado da cena (`SceneState`).
  - `controls/`: Gerencia a entrada do usuário (teclado e mouse).
  - `lightning/`: Configura a iluminação da cena.
  - `objects/`: Responsável por desenhar os objetos 3D.
- `Dockerfile`: Arquivo de receita para containerizar a aplicação com Docker, otimizado para WSLg.
