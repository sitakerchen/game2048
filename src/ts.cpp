#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "ts.h"


int ts_GetDirection()
{
	int fd = open("/dev/input/event0", O_RDWR);
	if (fd == -1)
	{
		printf("open event0 error\n");
		return -1;
	}
	struct input_event event0;
	int x_start = -1;
	int y_start = -1;
	int x_end = -1;
	int y_end = -1;
	while (1)
	{
		read(fd, &event0, sizeof(event0));
		if (EV_KEY == event0.type && BTN_TOUCH == event0.code && 0 == event0.value)
		{
			break;
		}
		if (EV_ABS == event0.type)
		{
			if (ABS_PRESSURE == event0.code && 0 == event0.value)
			{
				break;
			}
			if (ABS_X == event0.code)
			{
				if (x_start == -1)
				{
					x_start = event0.value;
				}
				x_end = event0.value;
			}
			if (ABS_Y == event0.code)
			{
				if (y_start == -1)
				{
					y_start = event0.value;
				}
				y_end = event0.value;
			}
		}
	}
	int direction_X = x_end - x_start;
	int direction_Y = y_end - y_start;
	if (abs(direction_X) > abs(direction_Y))
	{
		if (direction_X > 0)
		{
			return RIGHT;
		}
		else
		{
			return LEFT;
		}
	}
	else
	{
		if (direction_Y > 0)
		{
			return DOWN;
		}
		else
		{
			return UP;
		}
	}
	close(fd);
}

