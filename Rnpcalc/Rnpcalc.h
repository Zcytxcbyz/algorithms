#include <cmath>
#include <iostream>
#include <regex>
#include <map>
#include <stack>
#include <string>
#include <vector>
#define isword(str) ((str)>='A'&&(str)<='Z'||(str)>='a'&&(str)<='z')
#define isnum(str) ((str)>='0'&&(str)<='9')
#define iswordornum(str) (isword(str)||isnum(str))
#define iswordandnum(str) (isword(str)&&isnum(str))
#define isbrackets(str) ((str)=='('||(str)==')')
#define ischaracter(str) ((!isnum(str)&&str!='.')&&!isbrackets(str))
#define isoperand(str) ((isnum(str)||str=='.')&&!isbrackets(str))
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
map<const string, const int> Functions = {
	{"negate",1},{"abs",1},{"floor",1},{"ceil",1},{"round",1},
	{"pow",2},{"sqrt",1},{"log",2},{"lg",1},{"ln",1},
	{"exp",1},{"rand",0},{"randint",2},{"sin",1},{"cos",1},{"tan",1},
	{"asin",1},{"acos",1},{"atan",1},{"atan2",1},
	{"sinh",1},{"cosh",1},{"tanh",1},{"dec",1},{"rad",1},{"max",2},{"min",2}
};

struct function
{
	string name;
	vector<vector<string>> params;
};
vector<string> pretreat(string expr);
vector<vector<string>> retreat(vector<string> exprlist);
function functran(vector<string> expr);
int getpriority(string str);
vector<string> exprtran(vector<string> expr);
void ReplaceAll(string& str,string sub_str,string new_str) {
	while (str.find(sub_str)!=string::npos)
	{
		str.replace(str.find(sub_str), sub_str.length(), new_str);
	}
}