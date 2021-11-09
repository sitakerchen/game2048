/*************************************************************************
	> File Name: main.cpp
	> Author: csgec
	> Mail: 12345678@qq.com
	> Created Time: 2021年06月06日 星期日 10时02分26秒
 ************************************************************************/
#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <unistd.h>
#include "display.h"
#include "lcd.h"
#include "bmp.h"
#include "ts.h"
#include "ALG.h"
#include "io.h"
using namespace std;
typedef long long ll;
 /*
  * /IOT/cxl_px_2048/
  *
  * 400, 240, 140, 98
  *
  *
  *
  *
  */

extern bool flag;

int main()
{
	vector<string> pic_name; // picture name array
	vector<string> pic_full; // picture with relative path and name
	string pic_path = "./pic"; // path name where store the picture
	io_get_filelist_from_dir(pic_path, pic_name); // get the pic name array
	int pic_size = pic_name.size();
	auto cmp = [&](string a, string b)
	{
		int pos1 = a.find('.');
		int pos2 = b.find('.');
		int aa = stoi(a.substr(0, pos1));
		int bb = stoi(b.substr(0, pos2));
		return aa <= bb;
	};
	sort(pic_name.begin(), pic_name.end(), cmp); // 0 2 4 8 16 32 64 128 256 512 1024 2048 
	// index : (0 ~ 11)
	for (int i = 0 ; i < pic_size ; ++ i) pic_full.push_back(pic_path + "/" + pic_name[i]);

	OpenLcd();
	lcd_init(DIS_RED);

	cout << "test begin: " << endl;
	for (auto name : pic_name)
	{
		cout << name << endl;
		for (int i = 0 ; i < 400 ; ++ i)
			for (int j = 0 ; j < 2e3 ; ++ j);
	}
	cout << "test end" << endl;

	alg_init(pic_full);	alg_refresh();
	while (alg_randSite() != 1)
	{
		sleep(1);
		alg_refresh();
		while (1)
		{
			int dir = ts_GetDirection();
			if (dir == RIGHT)
			{
				alg_slide(1, 0, 3, false); // 1 : 右滑，原矩阵	
				alg_merge(1, 0, 3, false); 
				break;
			}
			else if (dir == LEFT)
			{
				alg_slide(-1, 0, 3, false); // 2 : 左滑，原矩阵
				alg_merge(-1, 0, 3, false);
				
				break;
			}
			else if (dir == UP)
			{
				alg_slide(-1, 0, 3, true); // 转置矩阵
				alg_merge(-1, 0, 3, true);
				break;
			}
			else if (dir == DOWN)
			{
				alg_slide(1, 0, 3, true);
				alg_merge(1, 0, 3, true);
				break;
			}
			else
			{
				break;
			}
		}
		alg_refresh();
	}
	lcd_init(DIS_RED);
	if (flag)
	{
		BmpTransmit("./win.bmp", 0, 0); // replace with .bmp format
	}
	else
	{
		BmpTransmit("./lose.bmp", 0, 0);
	}
	CloseLcd();
	return 0;
}

