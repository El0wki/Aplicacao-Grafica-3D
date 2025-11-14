# 1. Usar uma imagem base com compilador
FROM ubuntu:22.04

# Evitar prompts interativos durante a instalação
ENV DEBIAN_FRONTEND=noninteractive

# 2. Instalar as dependências do OpenGL e FreeGLUT
RUN apt-get update && apt-get install -y \
    build-essential \
    freeglut3-dev \
    libglu1-mesa-dev \
    && rm -rf /var/lib/apt/lists/*

# 3. Definir o diretório de trabalho dentro do contêiner
WORKDIR /app

# 4. Copiar a pasta 'src' e seu conteúdo para o contêiner
COPY src/ .

# 5. Compilar o código com os novos caminhos
#    -Ilightning: Adiciona a pasta 'lightning' aos caminhos de busca de includes
RUN g++ main.cpp lightning/lights.cpp -Ilightning -o aplicacao -lGL -lGLU -lglut

# 6. Definir o comando padrão para executar a aplicação
CMD ["./aplicacao"]