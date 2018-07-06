#!/bin/sh
gcc -DDOS -o m68kmake.exe src/cpu/m68000/m68kmake.c
mkdir -p xmame.obj/cpu/m68000
cp m68kmake.exe xmame.obj/cpu/m68000
xmame.obj/cpu/m68000/m68kmake.exe src/cpu/m68000 src/cpu/m68000/m68k_in.c
xmame.obj/cpu/m68000/m68kmake.exe xmame.obj/cpu/m68000 src/cpu/m68000/m68k_in.c

