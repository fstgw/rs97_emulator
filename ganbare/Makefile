DEBUG = 0

ifeq ($(DEBUG),0)
  CC = mipsel-linux-gcc
  LD = mipsel-linux-ld
  CFLAGS  = -O3 -mips32 -DGCW -Wall -I/home/steward/Downloads/buildroot-2017.02.9/output/host/usr/mipsel-buildroot-linux-uclibc/sysroot/usr/include/SDL
else
  CC = gcc
  LD = ld
  CFLAGS  = -O3 -DGCW -Wall -I/usr/include/SDL
endif
CXXFLAGS = $(CFLAGS)
LDFLAGS = -lSDL -lSDLmain -lm -lSDL_mixer -lSDL_image

OBJS  = src/ram.o src/util_snd.o src/function.o src/dconv.o src/scene.o src/title.o src/init.o src/act.o src/option.o src/ending.o src/logo.o src/refresh.o
SOURCES = $(patsubst %.o, %.c, $(OBJS))

all: gnp

gnp: $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)
	
clean:
	rm $(OBJS)
