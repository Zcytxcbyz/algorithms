#pragma once
#include <cmath>
#include <iostream>
#include <regex>
#include <stack>
#include <string>
#include <vector>
using namespace std;

vector<string> petreat(string expr);
vector<string> transexpr(vector<string> expr);
double calculate(vector<string> expr);
bool isoperand(string str);
bool ischaracter(char str);
int getpriority(char str);
