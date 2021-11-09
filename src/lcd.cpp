#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include "lcd.h"

int fd = -1;
unsigned int* pLCD = (unsigned int*)MAP_FAILED;


int OpenLcd()
{
	fd = open("/dev/fb0", O_RDWR);
	if (fd == -1)
	{
		printf("open fb0 error \n");
		return -1;
	}

	pLCD = (unsigned int*)mmap(NULL, 480 * 800 * 4, PROT_READ | PROT_WRITE,
		MAP_SHARED, fd, 0);
	if (MAP_FAILED == pLCD)
	{
		printf("mmap error!\n");
		return -1;
	}

	return 0;
}
void BrushPoint(int x, int y, unsigned int color)
{
	*(pLCD + x + 800 * y) = color;
}
int CloseLcd()
{
	if (MAP_FAILED != pLCD)
	{
		munmap(pLCD, 480 * 800 * 4);
	}
	if (fd != -1)
	{
		close(fd);
	}
	return 0;
}

int lcd_init(unsigned int col)
{
	for (int y = 0 ; y < 480 ; ++ y)
		for (int x = 0 ; x < 800 ; ++ x)
		{
			*(pLCD + y * 800 + x) = col;
		}
	return 0;
}

