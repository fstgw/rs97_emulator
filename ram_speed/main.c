#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#define CLK_BASE  	0x10000000
#define CPCCR     	(0x00 >> 2)
#define CPPCR     	(0x10 >> 2)
#define CPPSR     	(0x14 >> 2)
#define CPPCR1    	(0x30 >> 2)
#define CPSPR     	(0x34 >> 2)
#define CPSPPR    	(0x38 >> 2)
#define USBPCR    	(0x3C >> 2)
#define USBRDT    	(0x40 >> 2)
#define USBVBFIL  	(0x44 >> 2)
#define USBCDR    	(0x50 >> 2)
#define I2SCDR    	(0x60 >> 2)
#define LPCDR     	(0x64 >> 2)
#define MSCCDR    	(0x68 >> 2)
#define UHCCDR    	(0x6C >> 2)
#define SSICDR    	(0x74 >> 2)
#define CIMCDR    	(0x7C >> 2)
#define GPSCDR    	(0x80 >> 2)
#define PCMCDR    	(0x84 >> 2)
#define GPUCDR    	(0x88 >> 2)


#define RAM_BASE		0x13020000
#define DSTATUS 		(0x00 >> 2)
#define DCFG 				(0x04 >> 2)
#define DCTRL 			(0x08 >> 2)
#define DLMR 				(0x0C >> 2)
#define DTIMING1 		(0x10 >> 2)
#define DTIMING2 		(0x14 >> 2)
#define DREFCNT 		(0x18 >> 2)
#define DDQS 				(0x1C >> 2)
#define DDQSADJ 		(0x20 >> 2)
#define DMMAP0 			(0x24 >> 2)
#define DMMAP1 			(0x28 >> 2)
#define DDELAYCTRL1	(0x2C >> 2)
#define DDELAYCTRL2	(0x30 >> 2)

#define PAGE_SIZE	1024

int fd=-1;
volatile unsigned long *mem;

int map_it(unsigned long addr, unsigned long size)
{
  fd = open("/dev/mem", O_RDWR | O_SYNC);
  if(fd < 0){
    printf("failed to open /dev/mem\n");
    return -1;
  }
  mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr);
	return 0;
}

void unmap_it(unsigned long size)
{
	munmap((void*)mem, size);
	close(fd);
}

int main(int argc, char* argv[])
{
	uint32_t dma_addr;

	map_it(RAM_BASE, PAGE_SIZE);
	printf("DSTATUS: 0x%x\n", mem[DSTATUS]);
	printf("DCFG: 0x%x\n", mem[DCFG]);
	printf("DCTRL: 0x%x\n", mem[DCTRL]);
	printf("DLMR: 0x%x\n", mem[DLMR]);
	printf("DTIMING1: 0x%x\n", mem[DTIMING1]);
	printf("DTIMIMG2: 0x%x\n", mem[DTIMING2]);
	printf("DREFCNT: 0x%x\n", mem[DREFCNT]);
	printf("DDQS: 0x%x\n", mem[DDQS]);
	printf("DDQSADJ: 0x%x\n", mem[DDQSADJ]);
	printf("DMMAP0: 0x%x\n", mem[DMMAP0]);
	printf("DMMAP1: 0x%x\n", mem[DMMAP1]);
	printf("DDELAYCTRL1: 0x%x\n", mem[DDELAYCTRL1]);
	printf("DDELAYCTRL2: 0x%x\n", mem[DDELAYCTRL2]);
	mem[DTIMING1] = 0x10001000; //0x31114111
	mem[DTIMING2] = 0x4400; //0x8f11
	mem[DDQSADJ] = 0x2121; //0x2321
	unmap_it(PAGE_SIZE);	
  return 0;    
}

