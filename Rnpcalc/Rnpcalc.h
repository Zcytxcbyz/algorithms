#include <cmath>
#include <iostream>
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

map<string, double> Constants =
{
	{"PI",3.1415926535898},
	{"E",2.718281828459}
};
map<const string, const int> Symbols =
{
	{"+",8},{"-",8},{"*",9},{"/",9},{"%",9},
	{"!",10},{"&&",1},{"||",0},
	{"==",5},{">",6},{"<",6},{">=",6},{"<=",6},{"!=",5},
	{"&",4},{"|",2},{"^",3},{"~",10},{"<<",7},{">>",7},
	{"?",-1},{":",-1}

};

struct function
{
	string name;
	vector<vector<string>> params;
};
double calculation(string expr);
vector<string> pretreat(string expr);
vector<vector<string>> retreat(vector<string> exprlist);
function functran(vector<string> expr);
int getpriority(string str);
vector<string> exprtran(vector<string> expr);
double exprcalc(vector<string>expr);
double funccalc(function expr);
void ReplaceAll(string& str,string sub_str,string new_str) {
	while (str.find(sub_str)!=string::npos)
	{
		str.replace(str.find(sub_str), sub_str.length(), new_str);
	}
}