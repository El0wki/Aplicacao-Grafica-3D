# Aplicação Gráfica 3D com OpenGL

Este projeto demonstra a criação de uma cena 3D interativa utilizando C++ com as bibliotecas OpenGL e FreeGLUT. O código é modular, separando responsabilidades para facilitar manutenção, estudo e expansão.

## Funcionalidades

- **Cena 3D Completa:** Renderização de objetos primitivos (chão, cubo, cone, esfera, pêndulo animado).
- **Estrutura Modular:** Código-fonte organizado em `core`, `controls`, `lightning`, `objects`, `animations` e `textures`.
- **Textura Procedural:** O chão utiliza textura quadriculada gerada em tempo de execução.
- **Controle de Câmera FPS:** Movimentação pelo teclado (WASD, Q/E) e rotação pelo mouse.
- **Iluminação:** Sistema de luz ambiente e direcional (sol), com suporte a spotlight.
- **Animação Universal:** Todas as animações (bola, pêndulo, etc.) podem ser ativadas/desativadas juntas pela tecla espaço.
- **Pêndulo Animado:** Pêndulo físico com atributos personalizáveis (amplitude, velocidade, cor, comprimento) e movimento oscilatório realista.
- **Estrutura de Estado Centralizado:** Todas as propriedades da cena são gerenciadas por uma struct global (`SceneState`).

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

Pode ser necessário fechar e reabrir o terminal para completar a atualização. Execute o comando novamente se solicitado. 3. **Instale as ferramentas de compilação e o FreeGLUT:**

```bash
pacman -S mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-freeglut
```

#### 2. Compile e Execute o Projeto

1.  **Abra o terminal MSYS2 UCRT64** e navegue até a raiz do projeto:

```bash
cd /c/Users/rafae/Github/Classificadores/Aplicacao-Grafica-3D
```

2.  **Compile o projeto usando o Makefile:**

```bash
make
```

3.  **Execute a aplicação na raiz do projeto:**

```bash
./aplicacao.exe
```

---

### Método 2: Usando Docker com WSLg (Alta Performance e Containerizado)

Este método usa a tecnologia WSLg do Windows 11 para rodar a aplicação gráfica dentro de um contêiner Docker com aceleração de hardware, garantindo um ambiente consistente e de alta performance.

#### 1. Instale as Dependências (WSL/Ubuntu)

1.  **Instale o WSL e o Ubuntu:**

    - Abra a **Microsoft Store**, procure por **"Ubuntu 22.04 LTS"** e instale.
    - Abra o aplicativo Ubuntu pelo Menu Iniciar. Na primeira execução, ele pedirá para você criar um **nome de usuário** e uma **senha**.

2.  **Instale o Docker no Ubuntu:**

    - Siga as instruções oficiais: https://docs.docker.com/engine/install/ubuntu/

3.  **Verifique a aceleração gráfica:**
    - No terminal do Ubuntu:
      ```bash
      sudo apt-get update
      sudo apt-get install mesa-utils
      glxinfo | grep "OpenGL renderer"
      ```
    - A saída deve mostrar o nome da sua placa de vídeo (ex: NVIDIA, AMD, Intel).

#### 2. Compile e Execute com Docker

1.  **Abra o terminal do Ubuntu (WSL)** e navegue até a raiz do projeto:
    ```bash
    cd /mnt/c/Users/rafae/Github/Classificadores/Aplicacao-Grafica-3D
    ```
2.  **Construa a imagem Docker:**
    ```bash
    docker build -t app-grafica .
    ```
3.  **Execute o contêiner:**
    ```bash
    docker run -it --rm -e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix app-grafica
    ```
    A janela da aplicação deve abrir, rodando de forma fluida.

**Observação:**

- O executável gerado no Docker será chamado `aplicacao` (sem `.exe`).
- O build e execução são feitos sempre a partir da raiz do projeto, via terminal.
- O comando de compilação dentro do contêiner é sempre `make`, aproveitando o Makefile do projeto.
- Se for compilar manualmente dentro do Ubuntu/WSL, instale o make e as dependências:
  ```bash
  sudo apt-get update
  sudo apt-get install build-essential make freeglut3-dev libglu1-mesa-dev libgl1-mesa-glx
  make
  ./aplicacao
  ```

---

## Controles

- **W / S**: Mover para frente / trás
- **A / D**: Mover para os lados (strafe)
- **Q / E**: Mover a câmera para cima / baixo
- **Mouse**: Controla a direção da câmera (olhar para cima, baixo, lados)
- **Barra de Espaço**: Inicia/para todas as animações (bola, pêndulo, etc.)
- **ESC**: Fecha a aplicação

## Estrutura do Projeto

- `src/`: Todo o código-fonte, dividido em módulos:
  - `main.cpp`: Ponto de entrada, inicialização e loop principal
  - `core/`: Estruturas de dados centrais (`state.h`), controles de entrada (`controls`)
  - `lightning/`: Gerenciamento de iluminação
  - `objects/`: Desenho dos objetos 3D
  - `animations/`: Lógica de animação dos objetos
  - `textures/`: Geração e aplicação de texturas

## Princípios Básicos do C++ Utilizados

- **Structs e Classes:** Organizam dados e lógica separadamente
- **Encapsulamento:** Cada manager cuida de uma parte (entrada, animação, desenho)
- **Headers (.h) e Implementação (.cpp):** Separação clara entre declaração e lógica
- **Estado Centralizado:** Facilita acesso e modificação dos dados da cena

## Aspectos do GLUT (OpenGL Utility Toolkit)

- **GLUT:** Biblioteca para criar janelas, gerenciar eventos e facilitar o uso do OpenGL
- **Funções Principais:**
  - `glutInit`: Inicializa GLUT
  - `glutCreateWindow`: Cria a janela
  - `glutDisplayFunc`: Define a função de desenho
  - `glutKeyboardFunc`: Define a função de teclado
  - `glutPassiveMotionFunc`: Define a função de movimento do mouse
  - `glutTimerFunc`: Cria um loop de animação chamando uma função periodicamente
- **Ciclo de Vida:**
  1. Inicializa GLUT e OpenGL
  2. Registra funções de callback (desenho, teclado, mouse, timer)
  3. Entra no loop principal (`glutMainLoop`), respondendo a eventos e redesenhando a cena

## Fluxo Simplificado do Projeto

1. **Inicialização:** Instancia managers e estado global, inicializa GLUT e configura janela
2. **Entrada do Usuário:** Usuário interage via teclado/mouse, controles atualizam o estado global
3. **Animação:** Função timer chama animações periodicamente, managers atualizam propriedades animáveis
4. **Desenho:** Função display desenha todos os objetos usando o estado atual, OpenGL renderiza a cena

## Dicas de Estudo

- Explore o código para entender como C++ organiza dados e lógica
- Experimente modificar atributos dos objetos no estado para ver efeitos na cena
- Teste adicionar novos objetos ou animações seguindo o padrão modular
- Consulte a documentação do OpenGL e GLUT para aprofundar conceitos gráficos

---

## Estrutura do Projeto

## Sobre o Docker

- `Dockerfile`: Permite rodar a aplicação em ambiente containerizado, ideal para garantir compatibilidade e performance gráfica em qualquer máquina com WSLg.
