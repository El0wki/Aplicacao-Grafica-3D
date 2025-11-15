# 1. Usar uma imagem base com compilador
FROM ubuntu:22.04

# Evitar prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# 2. Instalar as dependências do OpenGL e FreeGLUT
RUN apt-get update && apt-get install -y \
    build-essential \
    freeglut3-dev \
    libglu1-mesa-dev \
    libgl1-mesa-glx \
    && rm -rf /var/lib/apt/lists/*

# 3. Configurar as variáveis de ambiente para o WSLg
ENV DISPLAY=:0
ENV LIBGL_ALWAYS_INDIRECT=0

# 4. Definir o diretório de trabalho dentro do contêiner
WORKDIR /app

# 5. Copiar a pasta 'src' e seu conteúdo para o contêiner
COPY src/ .

# 6. Compilar o código
#    Removemos as referências ao diretório 'ui' que não existe
RUN g++ main.cpp \
    lightning/lights.cpp \
    objects/objects.cpp \
    controls/controls.cpp \
    -Icore -Ilightning -Iobjects -Icontrols \
    -o aplicacao -lGL -lGLU -lglut

# 7. Definir o comando padrão para executar a aplicação
CMD ["./aplicacao"]