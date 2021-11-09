/*************************************************************************
	> File Name: io.cpp
	> Author: csgec
	> Mail: 12345678@qq.com 
	> Created Time: 2021年06月08日 星期二 08时46分57秒
 ************************************************************************/

#include <iostream>
#include <cstring>
#include <dirent.h>
#include <sys/types.h>
#include <vector>
using namespace std;

bool io_get_filelist_from_dir(string _path, vector<std::string> &_files)
{
	DIR *d = opendir(_path.c_str());
	if (d == NULL)
	{
		cout << "opendir error!" << endl;
		return false;
	}
	struct dirent * entry;
	while ((entry = readdir(d)) != NULL)
	{
		string file_name = entry->d_name;
		if (file_name == "." or file_name == "..") continue;
		_files.push_back(file_name);
	}
	return true;
}

