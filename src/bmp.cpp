#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "lcd.h"
#include "bmp.h"
void BmpTransmit(const char* pathname, int dx, int dy)
{
	int width = 0, high = 0, depth = 0;
	int fd1 = 0;
	fd1 = open(pathname, O_RDWR);
	lseek(fd1, 0x12, SEEK_SET);
	read(fd1, &width, 4);
	lseek(fd1, 0x16, SEEK_SET);
	read(fd1, &high, 4);
	lseek(fd1, 0x1c, SEEK_SET);
	read(fd1, &depth, 2);
	int lineValidByte = 0;//一行有效数据的长度
	int hunzi = 0;//一行数据的混子数
	int lineByte = 0;//一行数据的总字节数
	int totle = 0;//像素数组占多少个字节
	lineValidByte = (depth / 8) * width;
	if (lineValidByte % 4)
	{
		hunzi = 4 - (lineValidByte % 4);
	}
	lineByte = lineValidByte + hunzi;
	totle = lineByte * high;
	unsigned char* pPixelData = (unsigned char*)malloc(totle);
	lseek(fd1, 0x36, SEEK_SET);
	read(fd1, pPixelData, totle);
	int x = 0, y = 0;
	unsigned char ARGB_A = 0, ARGB_R = 0, ARGB_G = 0, ARGB_B = 0;
	unsigned int ARGB = 0;
	int i = 0;
	int color = 0;
	for (y = 0; y < high; y++)
	{
		for (x = 0; x < width; x++)
		{
			if (depth == 32)
			{
				ARGB_A = pPixelData[i++];
			}
			ARGB_R = pPixelData[i++];
			ARGB_G = pPixelData[i++];
			ARGB_B = pPixelData[i++];
			//ARGB = ARGB_A * 0x1000000 + ARGB_R * 0x10000 +ARGB_G * 0x100 +ARGB_B;
			ARGB = (ARGB_A << 24) | (ARGB_R << 16) | (ARGB_G << 8) | ARGB_B;
			if (x + dx < 800 && y + dy < 480)
			{
				BrushPoint(x + dx, high - y + dy - 1, ARGB);// location
				//color[high - y -1][x] = ARGB;
			}
		}
		i = i + hunzi;
	}
}
