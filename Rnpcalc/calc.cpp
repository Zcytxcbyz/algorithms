﻿#define DISABLED
#ifndef DISABLED
#define RELEASE
#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>
using namespace std;

vector<string> cutting(string expr);
vector<string> transexpr(vector<string> expr);
double calculate(vector<string> expr);
bool isoperand(string str);
bool ischaracter(char str);
int getpriority(char str);

#ifndef DEBUG
int main(int argc, char* argv[])
{
	if (argc == 2)
	{
		vector<string> expr = cutting(argv[1]);
		vector<string> rnp = transexpr(expr);
		cout << calculate(rnp);
	}
}
#else
int main()
{
	string input;
	cout << "Expression: ";
	cin >> input;
	vector<string> expr = cutting(input);
	for (auto inter = expr.begin(); inter != expr.end(); ++inter)
	{
		cout << *inter;
		if (inter != expr.end() - 1)
			cout << " ";
		else
			cout << endl;
	}
	vector<string> rnp = transexpr(expr);
	for (auto inter = rnp.begin(); inter != rnp.end(); ++inter)
	{
		cout << *inter;
		if (inter != rnp.end() - 1)
			cout << " ";
		else
			cout << endl;
	}
	cout << calculate(rnp) << endl;
	system("pause");
}
#endif

vector<string> cutting(string expr)
{
	int k = 0;
	vector<string> result;
	for (int i = 0; i < expr.length(); i++)
	{
		if (ischaracter(expr[i]) || expr[i] == '(' || expr[i] == ')')
		{
			if (!(expr[i] == '-' && (i == 0 ? true : (ischaracter(expr[i - 1]) || expr[i - 1] == '('))))
			{
				if (i != k)result.push_back(expr.substr(k, i - k));
				result.push_back(string(1, expr[i]));
				k = i + 1;
			}
		}
		if (i == expr.length() - 1 && k < expr.length())
		{
			result.push_back(expr.substr(k));
		}
	}
	return result;
}

vector<string> transexpr(vector<string> expr)
{
	vector<string> output;
	stack<char> op_stack;
	for (int i = 0; i < expr.size(); i++)
	{
		if (isoperand(expr[i]))
		{
			output.push_back(expr[i]);
		}
		else if (expr[i].length() == 1 && expr[i][0] == '(')
		{
			op_stack.push(expr[i][0]);
		}
		else if (expr[i].length() == 1 && expr[i][0] == ')')
		{
			while (!op_stack.empty() && op_stack.top() != '(')
			{
				output.push_back(string(1, op_stack.top()));
				op_stack.pop();
			}
			if (op_stack.top() == '(')
			{
				op_stack.pop();
			}
		}
		else if (expr[i].length() == 1 && ischaracter(expr[i][0]))
		{
			if (op_stack.empty())
			{
				op_stack.push(expr[i][0]);
			}
			else
			{
				while (!op_stack.empty() && getpriority(expr[i][0]) <= getpriority(op_stack.top()))
				{
					output.push_back(string(1, op_stack.top()));
					op_stack.pop();
				}
				op_stack.push(expr[i][0]);
			}
		}
	}
	while (!op_stack.empty())
	{
		output.push_back(string(1, op_stack.top()));
		op_stack.pop();
	}
	return output;
}

double calculate(vector<string> expr)
{
	stack<double> t_stack;
	for (int i = 0; i < expr.size(); i++)
	{
		if (isoperand(expr[i]))
		{
			t_stack.push(atof(expr[i].c_str()));
		}
		else if (expr[i].length() == 1 && ischaracter(expr[i][0]))
		{
			double a = t_stack.top();
			t_stack.pop();
			double b = t_stack.top();
			t_stack.pop();
			switch (expr[i][0])
			{
			case '+':t_stack.push(b + a); break;
			case '-':t_stack.push(b - a); break;
			case '*':t_stack.push(b * a); break;
			case '/':t_stack.push(b / a); break;
			case '^':t_stack.push(pow(b, a)); break;
			case '&':t_stack.push(b && a); break;
			case '|':t_stack.push(b || a); break;
			default:break;
			}
		}
	}
	return t_stack.top();
}

bool isoperand(string str)
{
	return regex_match(str, regex("^-?[0-9]+(.[0-9]+)?$"));
}

bool ischaracter(char str)
{
	return
		str == '+' ||
		str == '-' ||
		str == '*' ||
		str == '/' ||
		str == '^';
}

int getpriority(char str)
{
	switch (str)
	{
	case '+':return 0; break;
	case '-':return 0; break;
	case '*':return 1; break;
	case '/':return 1; break;
	case '^':return 2; break;
	default:return -1; break;
	}
}

#endif