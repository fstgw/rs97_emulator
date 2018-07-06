#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define GPIO_BASE 	0x10010000
#define PAPIN     	((0x10010000 - GPIO_BASE) >> 2)
#define PADAT				((0x10010010 - GPIO_BASE) >> 2)
#define PASET				((0x10010014 - GPIO_BASE) >> 2)
#define PACLR				((0x10010018 - GPIO_BASE) >> 2)
#define PBPIN				((0x10010100 - GPIO_BASE) >> 2)
#define PBDAT				((0x10010110 - GPIO_BASE) >> 2)
#define PBSET				((0x10010114 - GPIO_BASE) >> 2)
#define PBCLR				((0x10010118 - GPIO_BASE) >> 2)
#define PCPIN				((0x10010200 - GPIO_BASE) >> 2)
#define PCDAT				((0x10010210 - GPIO_BASE) >> 2)
#define PCSET				((0x10010214 - GPIO_BASE) >> 2)
#define PCCLR				((0x10010218 - GPIO_BASE) >> 2)
#define PDPIN				((0x10010300 - GPIO_BASE) >> 2)
#define PDDAT				((0x10010310 - GPIO_BASE) >> 2)
#define PDSET				((0x10010314 - GPIO_BASE) >> 2)
#define PDCLR				((0x10010318 - GPIO_BASE) >> 2)
#define PEPIN				((0x10010400 - GPIO_BASE) >> 2)
#define PEDAT				((0x10010410 - GPIO_BASE) >> 2)
#define PESET				((0x10010414 - GPIO_BASE) >> 2)
#define PECLR				((0x10010418 - GPIO_BASE) >> 2)
#define PFPIN				((0x10010500 - GPIO_BASE) >> 2)
#define PFDAT				((0x10010510 - GPIO_BASE) >> 2)
#define PFSET				((0x10010514 - GPIO_BASE) >> 2)
#define PFCLR				((0x10010518 - GPIO_BASE) >> 2)

int fd=-1;
volatile unsigned long *mem;

int main(int argc, char* argv[])
{
	unsigned long cnt=0;

  fd=open("/dev/mem", O_RDWR);
  if(fd < 0){
    printf("failed to open /dev/mem\n");
    return -1;
  }
  mem  = mmap(0, 2048, PROT_READ | PROT_WRITE, MAP_SHARED, fd, GPIO_BASE);
	while(1){
  	/*
		printf("GPIOA:0x%x 0x%x, GPIOB:0x%x 0x%x, GPIOC:0x%x 0x%x, GPIOD:0x%x 0x%x, GPIOE:0x%x 0x%x, GPIOF:0x%x 0x%x\n", 
			mem[PAPIN], mem[PADAT],
			mem[PBPIN], mem[PBDAT],
			mem[PCPIN], mem[PCDAT],
			mem[PDPIN], mem[PDDAT],
			mem[PEPIN], mem[PEDAT],
			mem[PFPIN], mem[PFDAT]
		);
		*/
		if((mem[PAPIN] & 0x40000000) == 0){
			cnt+= 1;
			if(cnt >= 10){
				system("poweroff");
				break;
			}
		}
		else{
			cnt = 0;
		}
		usleep(1000000);
	}
	munmap(mem, 2048);
	close(fd);
  return 0;    
}

