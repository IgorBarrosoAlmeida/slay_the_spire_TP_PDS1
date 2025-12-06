# 🔥 Slay the Spire --- TP PDS1

**Sobre o Projeto**
Este projeto consiste em uma implementação inspirada jogo Slay the Spire, desenvolvida integralmente na linguagem C. O jogo foi criado como Trabalho Prático Final para a disciplina de Programação e Desenvolvimento de Software I (PDS1) da Universidade Federal de Minas Gerais (UFMG).

O objetivo pedagógico foi aplicar conceitos fundamentais de Ciência da Computação, incluindo alocação dinâmica de memória, manipulação de ponteiros, modularização e interação com bibliotecas multimídia externas.

Funcionalidades Principais
-   Sistema de Combate por Turnos: Implementação fiel da lógica de energia, ataque, defesa e uso de cartas.

-   Gerenciamento de Deck: Mecânicas de compra, descarte, embaralhamento e exaustão de cartas.

-   Inimigos com IA de Intenção: Os inimigos telegrafam seus movimentos, permitindo planejamento estratégico.

------------------------------------------------------------------------

## 📁 Estrutura do Projeto

    /
    ├── .vscode/          # Configurações do VSCode
    ├── assets/           # Recursos (imagens, dados etc.)
    ├── bin/              # Executáveis gerados após a compilação
    ├── include/          # Arquivos .h (headers)
    ├── lib/              # Bibliotecas próprias do projeto
    ├── src/              # Código-fonte principal (.c)
    ├── Makefile          # Script de build
    └── README.md         # Documentação do projeto

------------------------------------------------------------------------

## ⚙️ Como Compilar

**Windows (via MSYS2/MinGW):**
Recomenda-se o uso do MSYS2 para gerenciar pacotes.
```bash
pacman -S mingw-w64-x86_64-allegro
```

**Ubuntu / Linux Mint (Debian-based):** 
Abra o terminal e execute:
```bash 
sudo apt-get update sudo apt-get install build-essential git sudo apt-get install liballegro5-dev liballegro-image5-dev liballegro-ttf5-dev liballegro-audio5-dev liballegro-acodec5-dev liballegro-primitives5-dev
```

Certifique-se de ter:

-   **GCC** ou outro compilador C compatível\
-   **make**

### 🔧 Compilação

``` bash
make
```

O executável será gerado dentro da pasta:

    /bin

### 🧹 Limpar arquivos de compilação

``` bash
make clean
```

------------------------------------------------------------------------

## ▶️ Como Executar

``` bash
./bin/slay_the_spire.exe
```

------------------------------------------------------------------------

## 📚 Organização do Código

### `src/`

Contém a lógica principal do jogo --- mecânicas, interação, controle de
fluxo e implementação das funcionalidades declaradas nos headers.

### `include/`

Contém todos os arquivos `.h`, incluindo:

-   Estruturas de dados\
-   Declaração de funções\
-   Constantes\

### `lib/`

Biblioteca do allegro utilzada para a renderização gráfica do jogo

### `assets/`

Arquivos de apoio (contém o txt que define as caracteristicas do deck e as
imagens utilizadas no jogo, todas geradas utilizando o modelo nano banana do 
gemini).

## 🧾 Créditos

Desenvolvido por **Igor Barroso Almeida** como Trabalho Prático de
**PDS1**.
