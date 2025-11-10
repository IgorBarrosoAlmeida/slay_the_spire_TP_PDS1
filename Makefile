# ====================================
# CONFIGURAÇÕES DO ALLEGRO
# ====================================
ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

# ====================================
# PASTAS DO PROJETO
# ====================================
SRC_DIR=src
INC_DIR=include
BIN_DIR=bin
LIB_DIR=lib

# ====================================
# ARQUIVOS-FONTE E OBJETOS
# ====================================
SRC=$(wildcard $(SRC_DIR)/*.c)
OBJ=$(SRC:$(SRC_DIR)/%.c=$(BIN_DIR)/%.o)

# ====================================
# COMPILADOR E FLAGS
# ====================================
CC=gcc
CFLAGS=-I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I $(INC_DIR)
LDFLAGS=$(PATH_ALLEGRO)$(LIB_ALLEGRO)
TARGET=$(BIN_DIR)/meu_jogo.exe

# ====================================
# REGRAS PRINCIPAIS
# ====================================
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

# Compila cada .c da pasta src/ para .o na pasta bin/
$(BIN_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# ====================================
# LIMPEZA (compatível com Windows cmd)
# ====================================
clean:
	cmd /C del /Q $(BIN_DIR)\*.o 2>nul
	cmd /C del /Q $(TARGET) 2>nul

# ====================================
# EXECUTAR O JOGO (opcional)
# ====================================
run: all
	$(TARGET)
