/*************************************************************************
	> File Name: display.c
	> Author: csgec
	> Mail: 12345678@qq.com
	> Created Time: 2021年06月06日 星期日 10时02分47秒
 ************************************************************************/
#include <stdio.h>
#include <sys/types.h> 
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "lcd.h"
#include "display.h"
uint color[DIS_LONG][DIS_WIDTH];
// const int mode[3] = 
// {
// 	O_RDONLY,
// 	O_WRONLY,
// 	O_RDWR,
// };
// /*******prepare to draw*********/
// int dis_open_mode(int m)
// {
// 	if (m > 2)
// 	{
// 		printf("parameter error!");
// 		return -1;
// 	}
// 	int fd = open("/dev/fb0", mode[m]);
// 	if (fd == -1)
// 	{
// 		printf("open fb0 error!\n");
// 		return -1;
// 	}
// 	return fd; // return file id
// }
// int dis_writeAndClose(int fd)
// {
//     int res  = write(fd,color,480*800*4);
// 	if(res != 480*800*4)
//     {
//         printf("write fb error!\n");
// 		return -1;
// 	}
// 	close(fd);
// 	return 0;
// }
 
// /*single color display, check screen*/ 
// int dis_test()
// {
// 	int fd = dis_open_mode(2);
//     int x,y;
// 	if (fd == -1) return fd;
// 	int RGBW [] = { DIS_RED, DIS_GREEN, DIS_BLUE, DIS_WHITE};
// 	for (int i = 0 ; i < 4 ; ++ i)
// 		for(y = 0;y<480;y++)
// 		{
// 			for(x = 0;x < 800;x++ )
// 			{
// 		        color[y][x] = RGBW[i];
// 				// unfinished, change per touch
//     	    }
// 		}
// 	dis_writeAndClose(fd);
// 	return 0;
// }

int dis_drawCircle(int Ox, int Oy, int radius, int seed)
{
	for (int y = 0; y < DIS_LONG; ++y)
		for (int x = 0; x < DIS_WIDTH; ++x)
		{
			if ((x - Ox) * (x - Ox) + (y - Oy) * (y - Oy) <= radius * radius)
			{
				if (color[y][x] == 0)color[y][x] = DIS_GREEN;
				else color[y][x] = color[y][x] | DIS_RED | (0x332211 >> seed);
			}
		}
	return 0;
}
int dis_drawRectangle(int y, int x, int edge, uint pic)
{
	for (int i = y; i < y + edge; ++i)
		for (int j = x; j < x + edge; ++j)
		{
			color[i][j] = pic;
		}
	return 0;
}
int dis_drawImage(int x, int y, int r, int len)
{
	memset(color, 0, sizeof color);
	OpenLcd();
	int dx[] = { -1, 1, -1, 1 };
	int dy[] = { -1, -1, 1, 1 };
	for (int i = 0; i < 4; ++i)
	{
		int nx = x + dx[i] * len;
		int ny = y + dy[i] * len;
		dis_drawCircle(nx, ny, r, i);
	}
	for (int i = 0; i < DIS_LONG; ++i)
		for (int j = 0; j < DIS_WIDTH; ++j)
		{
			if (color[i][j] == 0) color[i][j] = DIS_GREEN;
		}
	for (int i = 0; i < DIS_LONG; ++i)
		for (int j = 0; j < DIS_WIDTH; ++j)
		{
			int dist = (i - y) * (i - y) + (j - x) * (j - x);
			if (dist <= r * r + 2000 && dist >= r * r - 2000) color[i][j] = DIS_RED;
		}
	for (int i = 0; i < DIS_LONG; ++i)
		for (int j = 0; j < DIS_WIDTH; ++j)
			if (color[i][j] == DIS_GREEN) color[i][j] = DIS_WHITE;
	for (int i = 0; i < DIS_LONG; ++i)
		for (int j = 0; j < DIS_WIDTH; ++j)
		{
			BrushPoint(j, i, color[i][j]);  //  attention: i -> y , j -> x
		}
	CloseLcd();
	return 0;
}
int dis_implement()
{
	OpenLcd();
	for (int y = 0; y < DIS_LONG; ++y)
		for (int x = 0; x < DIS_WHITE; ++x)
			BrushPoint(x, y, color[y][x]);
	CloseLcd();
	return 0;
}
