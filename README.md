# Aplicação Gráfica 3D com OpenGL e Docker

Este é um projeto simples que demonstra a criação de uma cena 3D interativa utilizando C++ com as bibliotecas OpenGL e FreeGLUT. A aplicação é totalmente containerizada com Docker para garantir um ambiente de compilação e execução consistente, resolvendo problemas comuns de dependências em diferentes sistemas operacionais.

## Funcionalidades

- **Cena 3D:** Renderização de objetos primitivos (cubo, cone, esfera) para formar uma cena simples.
- **Textura Procedural:** O chão da cena utiliza uma textura quadriculada gerada em tempo de execução.
- **Controle de Câmera FPS:** Controle de câmera em primeira pessoa (First-Person Shooter) com movimentação pelo teclado e rotação pelo mouse.
- **Mira (Crosshair):** Uma mira fixa no centro da tela para auxiliar na navegação.
- **Iluminação:** Sistema de iluminação básico com uma fonte de luz direcional (simulando o sol) e uma luz ambiente para preenchimento.
- **Animação:** Animação simples de um objeto que pode ser iniciada e parada pelo usuário.

## Pré-requisitos

Para compilar e executar este projeto, você precisará de:

1.  **[Docker Desktop](https://www.docker.com/products/docker-desktop/)**: Para construir e rodar o contêiner da aplicação.
2.  **Um X Server para Windows**: Necessário para que a aplicação gráfica dentro do contêiner possa ser exibida no Windows. A opção recomendada é o **[VcXsrv](https://sourceforge.net/projects/vcxsrv/)**.

## Como Executar

Siga os passos abaixo para rodar a aplicação.

### 1. Configure o X Server (VcXsrv)

Antes de rodar o contêiner, o VcXsrv precisa estar em execução com a configuração correta.

1.  Inicie o **XLaunch** a partir do seu Menu Iniciar.
2.  Na primeira tela, selecione **"Multiple windows"** e clique em _Avançar_.
3.  Na segunda tela, selecione **"Start no client"** e clique em _Avançar_.
4.  Na terceira tela, **marque a caixa "Disable access control"**. Este é o passo mais importante.
5.  Clique em _Avançar_ e depois em _Concluir_. Um ícone do VcXsrv deve aparecer na sua bandeja do sistema (ao lado do relógio).

### 2. Construa a Imagem Docker

Abra um terminal (PowerShell, CMD, etc.) na pasta raiz deste projeto e execute o seguinte comando para construir a imagem:

```bash
docker build -t app-grafica .
```

### 3. Execute o Contêiner

Com o VcXsrv rodando e a imagem construída, execute o comando abaixo no mesmo terminal para iniciar a aplicação:

```bash
docker run --rm -it -e DISPLAY=host.docker.internal:0.0 app-grafica
```

A janela da aplicação 3D deverá aparecer na sua tela.

## Controles

- **W / S**: Mover para frente / trás.
- **A / D**: Mover para os lados (strafe).
- **Mouse**: Controlar a direção da câmera (olhar para cima, baixo, lados).
- **Q / E**: Mover a câmera para cima / baixo.
- **Barra de Espaço**: Iniciar / Parar a animação da bola.
- **ESC**: Fechar a aplicação.

## Estrutura do Projeto

- `main.cpp`: Contém todo o código-fonte da aplicação em C++/OpenGL. É responsável pela inicialização, renderização da cena, controle de câmera e gerenciamento de eventos de teclado e mouse.
- `Dockerfile`: Arquivo de receita que define o ambiente da aplicação. Ele instrui o Docker a usar uma imagem base do Ubuntu, instalar o compilador C++ e as dependências do FreeGLUT/OpenGL, e finalmente compilar e preparar o `main.cpp` para execução.
