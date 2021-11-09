/*************************************************************************
	> File Name: ALG.cpp
	> Author: csgec
	> Mail: 12345678@qq.com 
	> Created Time: 2021年06月08日 星期二 11时19分54秒
 ************************************************************************/

#include<iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>
#include <map>
#include <ctime>
#include <random>
#include "bmp.h"
#define fi first
#define se second
using namespace std;
typedef pair<int, int> pii;

//string board[4][4];
int game[4][4]; 
int remain;
bool flag = false;
map<int, string>  ma;

int alg_init(vector<string> pic_pathName)
{
	for (int y = 0 ; y < 4 ; ++ y)
		for (int x = 0 ; x < 4 ; ++ x)
		{
			//board[y][x] = pic_pathName[0];
			game[y][x] = 0;
		}

	ma[0] = pic_pathName[0];
	int cnt = 1;	
	for (int i = 2 ; i <= 2048 ; i += i)
	{
		ma[i] = pic_pathName[cnt++];
		cout << "i : " << i << " name : " << pic_pathName[cnt - 1] << endl;
	}
	remain = 16;
	flag = false;
	return 0;
}

int alg_randSite()
{
	vector<pii> empty;
	for (int y = 0 ; y < 4 ; ++ y)
		for (int x = 0 ; x < 4 ; ++ x)
		{
			if (game[y][x] == 0)
			{
				empty.push_back({y, x});
			}
			else if (game[y][x] >= 2048)
			{
				flag = true;
			}
		}

	if (flag) 
	{
		cout << "you win!" << endl;
		return 2;
	}

	remain = empty.size();

	for (int i = 0 ; i < 2 ; ++ i)
	{
		if (remain <= 0) 
		{
			cout << "game over!" << endl;
			return 1; // game over
		}
		srand((unsigned)time(NULL));
		int next = 0;
		next = rand() % empty.size();
		int ny = empty[next].fi;
		int nx = empty[next].se;
		empty.erase(empty.begin() + next);

		srand((unsigned)time(NULL));
		game[ny][nx] = (rand() % 2 + 1) * 2;
		cout << "rand : " << game[ny][nx] << endl;
		remain--;
	}
	return 0;
}

int alg_flush()
{
	for (int y = 0 ; y < 4 ; ++ y)
		for (int x = 0 ;x < 4 ; ++ x)
		{
			//cout << "path : " << board[y][x].c_str() << endl;
			cout << "ma : " << ma[game[y][x]] << endl;
			BmpTransmit(ma[game[y][x]].c_str(), 160 + x * 120, 0 + y * 120);
		}
	return 0;
}

int alg_slide(int dir, int l, int r, bool rev) // -1 : to left, 1 : to right, close area [l, r]
{
	if (flag)
	{
		cout << "you win!" << endl;
		return 2;
	}
	if (l >= r or l < 0) return 0;
	for (int y = 0 ; y <= 3 ; ++ y)
	{
		for (int x = l ; x <= r ; ++ x)
		{
			int next = x + dir;
			next = max(0, next);
			next = min(3, next);
			if (rev)
			{
				if (game[next][y] == 0 and game[x][y] != 0)
				{
					swap(game[x][y], game[next][y]);

					alg_slide(dir,x - 1 , x, rev);
				}
			}
			else 
			{
				if (game[y][next] == 0 and game[y][x] != 0) 
				{
					swap(game[y][x], game[y][next]);

					alg_slide(dir ,x - 1 , x, rev);
				}
			}
		}
	}
	return 0;
}

int alg_merge(int dir, int l, int r, bool rev)
{	
	if (flag) 
	{
		cout << "you win!" << endl;
		return 2;
	}
	if (l >= r or l < 0) return 0;
	for (int y = 0 ; y <= 3 ; ++ y)
	{
		for (int x = l ; x <= r ; ++ x)
		{
			int next = x + dir;
			next = max(0, next);
			next = min(3, next);
			if (rev)
			{
				if (game[next][y] ==  game[x][y] and next != x)
				{
					game[next][y] += game[x][y];
					game[x][y] = 0;

					if (game[next][y] >= 2048) 
					{
						flag = true;
						return 2;
					}
					alg_slide(dir, x - 1, x, rev);
				}
			}
			else 
			{
				if (game[y][next] == game[y][x] and next != x) 
				{
					game[y][next] += game[y][x];
					game[y][x] = 0;

					if (game[y][next] >= 2048) 
					{
						flag = true;
						return 2;
					}
					alg_slide(dir ,x - 1 , x, rev);
				}
			}
		}
	}
	return 0;
}

/***wrong algorithm***/
//int alg_oneStep(int dir, int rev)
//{
//	for (int y = 0 ; y <= 3 ; ++ y)
//	{
//		deque<int> dq;
//		for (int x = 0 ; x <=3 ; ++ x)
//		{
//			int xx = x, yy = y;
//			if (rev) swap(xx, yy);
//
//			int cur = game[yy][xx];
//
//			if (cur == 0) continue; // skip zero value
//			if (xx == 0) dq.push_back(cur);
//			else 
//			{
//				int back = dq.back();
//				if (back == cur)
//				{
//					dq.back() *= 2;
//				}
//				else
//				{
//					dq.push_back(cur);
//				}
//			}
//		}
//		if (dir == 1) reverse(dq.begin(), dq.end());
//		while (dq.size() < 4)
//		{
//			if (dir == 1) dq.push_front(0);
//			else dq.push_back(0);
//		}
//		for (int x = 0 ; x <= 3 ; ++ x)
//		{
//			if (rev) game[x][y] = dq[x];
//			else game[y][x] = dq[x];
//		}
//	}
//	return 0;
//}
