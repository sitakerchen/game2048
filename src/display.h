#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#define DIS_RED 0xff0000
#define DIS_GREEN 0x00ff00
#define DIS_BLUE 0x0000ff
#define DIS_WHITE 0xffffff

#define DIS_WIDTH 800
#define DIS_LONG  480

#define uint unsigned int

// function below just used for test or display victory picture
int dis_drawCircle(int x, int y, int, int);

int dis_drawRectangle(int, int, int, uint);

int dis_drawImage(int, int, int, int);

/*
 *
 * implement color into framebuffer
 *
 */
int dis_implement();

#endif
