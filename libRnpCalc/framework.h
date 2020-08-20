// header.h: 标准系统包含文件的包含文件，
// 或特定于项目的包含文件
//

#pragma once

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头文件中排除极少使用的内容
// Windows 头文件
#include <windows.h>
#include <cmath>
#include <regex>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include <ctime>
#define isword(str) ((str)>='A'&&(str)<='Z'||(str)>='a'&&(str)<='z')
#define isnum(str) ((str)>='0'&&(str)<='9')
#define iswordornum(str) (isword(str)||isnum(str))
#define iswordandnum(str) (isword(str)&&isnum(str))
#define isbrackets(str) ((str)=='('||(str)==')')
#define ischaracter(str) ((!isnum(str)&&str!='.')&&!isbrackets(str))
#define isoperand(str) ((isnum(str)||str=='.')&&!isbrackets(str))
#define randint(minval,maxval) ((rand() % (maxval-minval+1))+ minval)
using namespace std;