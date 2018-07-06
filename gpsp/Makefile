
TARGET := gpsp

CC := mipsel-linux-gcc
SDL_CONFIG := /home/steward/Downloads/buildroot-2017.02.9/output/host/usr/mipsel-buildroot-linux-uclibc/sysroot/usr/bin/sdl-config

OBJS := main.o cpu.o memory.o video.o input.o sound.o gui.o \
	cheats.o zip.o cpu_threaded.o mips_stub.o

CFLAGS := `$(SDL_CONFIG) --cflags` -Wall -O2 -fomit-frame-pointer -DZAURUS
ASFLAGS := $(CFLAGS)
LDFLAGS := `$(SDL_CONFIG) --libs` -lpthread -lz -lm

.PHONY: all $(TARGET) clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm -f $(TARGET) $(OBJS)
