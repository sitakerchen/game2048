#ifndef __LCD_H__
#define __LCD_H__

int OpenLcd();

void BrushPoint(int x, int y, unsigned int color);

int CloseLcd();

int lcd_init(unsigned int col);

#endif
