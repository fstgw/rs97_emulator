CC = mipsel-linux-gcc
LD = $(CC)
STRIP = mipsel-linux-strip

NAME=wizznic
TARGET= $(NAME).dge

DEFS = -DGP2X -DIS_LITTLE_ENDIAN -D_REENTRANT #-DGP2X_ASM

INCS =  -I.

CFLAGS= -mips32 -O3 -fstrength-reduce -fthread-jumps -fexpensive-optimizations -fomit-frame-pointer -frename-registers -pipe -G 0 -ffast-math
LDFLAGS=$(CFLAGS)
LIBS = -lSDL -lSDL_image -lSDL_mixer -lpng -lm -lz -lpthread

OBJS = board.o cursor.o draw.o input.o main.o menu.o sprite.o text.o ticks.o\
sound.o game.o player.o list.o levels.o wiz.o pixel.o stars.o levelselector.o\
leveleditor.o

MYCC = $(CC) $(CFLAGS) $(INCS) $(DEFS)

########################################################################

sdl: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@ $(LIBS)
	$(STRIP) $@

.c.o:
	$(MYCC) -c $< -o $@

clean:
	rm -f *.o *.dge
