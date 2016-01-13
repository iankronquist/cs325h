CC=g++
CFLAGS=-std=c99 -Werror -Wpedantic -Wall -Wextra

all: tri_tiling

tri_tiling: tri_tiling.c
	${CC} tri_tiling.c -o tri_tiling ${CFLAGS}
