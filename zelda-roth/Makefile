PROG = ZeldaROTH_US.dge
SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
CXX  = mipsel-linux-g++
SDL-CONFIG = /home/steward/Downloads/buildroot-2017.02.9/output/host/usr/mipsel-buildroot-linux-uclibc/sysroot/usr/bin/sdl-config

CXXFLAGS = -Wall -g `$(SDL-CONFIG) --cflags` -DDINGUX
LDFLAGS = `$(SDL-CONFIG) --libs` -lSDL_mixer -lSDL_image -lSDL_gfx

$(PROG): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(PROG)

clean:
	rm -f $(PROG) *.o

.PHONY: clean
