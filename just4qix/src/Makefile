CC=mipsel-linux-gcc
CFLAGS=-O2 -ffast-math
LIBS=-lSDL -lSDL_mixer

just4qix: main.o render.o update.o input.o sound.o particle.o
	$(CC) main.o render.o update.o input.o sound.o particle.o -o just4qix -lSDL -lSDL_mixer

clean:
	rm -rf *.o
	rm -rf just4qix
