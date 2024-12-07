# Tested with LLVM Clang on Windows11 with SDL2.30.10
# REMARKS: SDL2.dll is required

CC := clang
SDL_DIR := C:/lib/SDL2.30.10/

# project_root/
#   bin/
#   src/**/*.c
#   include/**/*.h

SRC_DIR := src/
INCLUDE_DIR := include/
BIN_DIR := bin/

#
# No need to change anything below here in normal use cases
#

CFLAGS := -Wall -Wextra -std=c99 -Wno-missing-braces
CFLAGS += -I$(SDL_DIR)include/ -I$(INCLUDE_DIR)
# REMARKS: SDL2 folder structure may change
LDFLAGS := -L$(SDL_DIR)lib/x64/

LIBS := -lSDL2 -lSDL2main
# These two are all for SDL2 to work on windows
LIBS += -lole32 -loleaut32 -limm32 -lversion -lShell32
LIBS += -lgdi32 -lwinmm -lsetupapi -luser32 -lkernel32

# Two wildcards because /**/*c doesnt capture /*.c
SRCS := $(wildcard $(SRC_DIR)*.c) $(wildcard $(SRC_DIR)**/*.c)

DEBUG_FLAGS := -g -O1 -UNDEBUG -Xlinker /subsystem:console
RELEASE_FLAGS := -O3 -DNDEBUG -Xlinker /subsystem:windows

debug:
	$(CC) -o $(BIN_DIR)$@.exe $(SRCS) $(DEBUG_FLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS)
	./$(BIN_DIR)$@

release:
	$(CC) -o $(BIN_DIR)$@.exe $(SRCS) $(RELEASE_FLAGS) $(CFLAGS) $(LDFLAGS) $(LIBS)

.PHONY: debug release