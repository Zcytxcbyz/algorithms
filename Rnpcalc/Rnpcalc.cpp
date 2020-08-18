#include "RnpCalc.h"

int main() {
// 	string expr = "8>sin(6-4)?8*15:-tan(-5+4/2.012,float(4))*12.89";
// 	auto result = retreat(pretreat(expr));
// 	for (int i = 0; i < result.size(); ++i) {
// 		for (int j = 0; j < result[i].size(); ++j) {
// 			cout << result[i][j];
// 			if (j != result[i].size() - 1) cout << " ";
// 		}
// 		cout << endl;
// 	}
	string expr = "(18*6)-4/8.23^2";
	vector<string> result = exprtran(retreat(pretreat(expr))[0]);
	for (auto iter = result.begin(); iter != result.end(); ++iter) {
		cout << *iter;
		if (iter == result.end() - 1) cout << endl;
		else cout << " ";
	}
	system("pause");
}
vector<string> pretreat(string expr) {
	ReplaceAll(expr, "PI", "3.1415926535898");
	ReplaceAll(expr, "E", "2.718281828459");
	for (int i = 0; i < expr.length(); ++i) {
		if (expr[i] == '-') {
			if (i != 0 ? !iswordornum(expr[i - 1]) && expr[i - 1] != ')' : true) {
				expr.insert(i, 1, '0');
				++i;
			}
		}
	}
	int n = 0;
	string result = expr;
	vector<string> fuc_exprs;
	string fuc_temps;
	stack<char> fucstac;
	for (char i:expr) {
		if (isword(i)) {
			fucstac.push(i);
		}
		else if (!fucstac.empty()) {
			if (i != ')') {
				fucstac.push(i);
			}
			else{
				do{
					fuc_temps.insert(fuc_temps.begin(), fucstac.top());
					fucstac.pop();
				}while (fucstac.top() != '(');
				if (fucstac.top() == '(') {
					do{
						fuc_temps.insert(fuc_temps.begin(), fucstac.top());
						fucstac.pop();
					}while(!fucstac.empty() && isword(fucstac.top()));
					fuc_temps.push_back(i);
					fuc_exprs.push_back(fuc_temps);
					result.replace(result.find(fuc_temps), fuc_temps.length(), "$" + to_string(n));
					if (!fucstac.empty()){
						fucstac.push('$');
						fucstac.push(n + '0');
					}
					++n;
					fuc_temps.clear();
				}
			}
		}
	}
	regex pattern("(\\(|^)([^?:]+)\\?([^?:]+):([^?:]+)(\\)|$)");
	smatch matches;
	while (regex_search(result, matches, pattern))
	{
		fuc_exprs.push_back(matches[2]);
		fuc_exprs.push_back(matches[3]);
		fuc_exprs.push_back(matches[4]);
		fuc_exprs.push_back("$" + to_string(n) + "?$" + to_string(n + 1) + ":$" + to_string(n + 2) + "");
		n += 3;
		result = regex_replace(result, pattern, "$1$$" + to_string(n) + "$5");
		++n;
	}
	fuc_exprs.push_back(result);
	return fuc_exprs;
}

vector<vector<string>> retreat(vector<string> exprlist) {
	vector<vector<string>> result;
	for (string expr : exprlist) {
		vector<string> result_item;
		string op_temp, nm_temp;
		for (int i = 0; i < expr.length(); ++i) {
			if (isbrackets(expr[i])) {
				if (!op_temp.empty()) {
					result_item.push_back(op_temp);
					op_temp.clear();
				}
				if (!nm_temp.empty()) {
					result_item.push_back(nm_temp);
					nm_temp.clear();
				}
				result_item.push_back(string(1, expr[i]));
			}
			else if (isoperand(expr[i]) || expr[i] == '$') {
				if (!op_temp.empty()) {
					result_item.push_back(op_temp);
					op_temp.clear();
				}
				nm_temp.push_back(expr[i]);

			}
			else if (ischaracter(expr[i])) {
				if (!nm_temp.empty()) {
					result_item.push_back(nm_temp);
					nm_temp.clear();
				}
				op_temp.push_back(expr[i]);
			}
		}
		if (!nm_temp.empty()) {
			result_item.push_back(nm_temp);
		}
		if (!op_temp.empty()) {
			result_item.push_back(op_temp);
		}
		result.push_back(result_item);
	}
	return result;
}

function functran(vector<string> expr)
{
	function result;
	vector<string> temp;
	result.name = expr[0];
	int k = 2;
	for (int i = 2; i < expr.size(); ++i)
	{
		if (expr[i].length() == 1 && (expr[i][0] == ',' || i == expr.size() - 1)) {
			for (int j = k; j < i; ++j) {
				temp.push_back(expr[j]);
			}
			result.params.push_back(temp);
		}
	}
	return result;
}

int getpriority(string str)
{
	map<const string, const int>::iterator iter = Symbols.find(str);
	return iter != Symbols.end() ? iter->second : -1;
}

vector<string> exprtran(vector<string> expr)
{
	vector<string> output;
	stack<string> op_stack;
	for (int i = 0; i < expr.size(); i++)
	{
		if (regex_match(expr[i],regex("-?\\d+(?:\\.\\d+)?")))
		{
			output.push_back(expr[i]);
		}
		else if (expr[i] == "(")
		{
			op_stack.push(expr[i]);
		}
		else if (expr[i] == ")")
		{
			while (!op_stack.empty() && op_stack.top() != "(")
			{
				output.push_back(op_stack.top());
				op_stack.pop();
			}
			if (op_stack.top() == "(")
			{
				op_stack.pop();
			}
		}
		else
		{
			if (op_stack.empty())
			{
				op_stack.push(expr[i]);
			}
			else
			{
				while (!op_stack.empty() && getpriority(expr[i]) <= getpriority(op_stack.top()))
				{
					output.push_back(op_stack.top());
					op_stack.pop();
				}
				op_stack.push(expr[i]);
			}
		}
	}
	while (!op_stack.empty())
	{
		output.push_back(op_stack.top());
		op_stack.pop();
	}
	return output;
}
