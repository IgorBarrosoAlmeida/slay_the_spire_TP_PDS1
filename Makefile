#ALLEGRO_VERSION=5.0.10
#MINGW_VERSION=4.7.0
#FOLDER=C:

#FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
#PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
#LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
#INCLUDE_ALLEGRO=\include

# Pasta local onde estão seus headers e .c
#INCLUDE_LOCAL=.\libs
#SRC=slay_the_spire.c \
#    libs/renderer.c \
#    libs/utils.c

#OBJ=$(SRC:.c=.o)

#game: $(OBJ)
#	gcc -o slay_the_spire.exe $(OBJ) $(PATH_ALLEGRO)$(LIB_ALLEGRO)

#%.o: %.c
#	gcc -I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I $(INCLUDE_LOCAL) -c $< -o $@

#clean:
#	del $(OBJ)
#	del slay_the_spire.exe

# ====================================
# Configurações Allegro
# ====================================
ALLEGRO_VERSION=5.0.10
MINGW_VERSION=4.7.0
FOLDER=C:

FOLDER_NAME=\allegro-$(ALLEGRO_VERSION)-mingw-$(MINGW_VERSION)
PATH_ALLEGRO=$(FOLDER)$(FOLDER_NAME)
LIB_ALLEGRO=\lib\liballegro-$(ALLEGRO_VERSION)-monolith-mt.a
INCLUDE_ALLEGRO=\include

# ====================================
# Pasta local
# ====================================
INCLUDE_LOCAL=.\libs
SRC_LOCAL=.\libs

# ====================================
# Detecta todos os arquivos .c
# ====================================
SRC=$(wildcard *.c) $(wildcard $(SRC_LOCAL)/*.c)
OBJ=$(SRC:.c=.o)

# ====================================
# Executável
# ====================================
EXE=slay_the_spire.exe

# ====================================
# Compilador e flags
# ====================================
CC=gcc
CFLAGS=-I $(PATH_ALLEGRO)$(INCLUDE_ALLEGRO) -I $(INCLUDE_LOCAL)

# ====================================
# Alvo principal
# ====================================
all: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(PATH_ALLEGRO)$(LIB_ALLEGRO)

# ====================================
# Regra para compilar qualquer .c em .o
# ====================================
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# ====================================
# Limpeza
# ====================================
clean:
	cmd /C del /Q *.o $(SRC_LOCAL)\*.o 2>nul
	cmd /C del /Q $(EXE) 2>nul
