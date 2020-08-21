#include "framework.h"
#include "RnpCalc.h"

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

vector<string> pretreat(string expr);
vector<vector<string>> retreat(vector<string> exprlist);
function functran(vector<string> expr);
int getpriority(string str);
vector<string> exprtran(vector<string> expr);
double exprcalc(vector<string>expr);
double funccalc(function expr);
void ReplaceAll(string& str, string sub_str, string new_str) {
	while (str.find(sub_str) != string::npos)
	{
		str.replace(str.find(sub_str), sub_str.length(), new_str);
	}
}

LIBRNPCALC_API double calculate(string expr) {
	srand(time(0));
	vector<double> result;
	auto rtexpr = retreat(pretreat(expr));	
	for (int i = 0; i < rtexpr.size(); ++i) {
		bool iscondition = false;
		for (int j = 0; j < rtexpr[i].size(); ++j) {
			if (rtexpr[i][j][0] == '$') {
				rtexpr[i][j] = to_string(result.at(stoi(rtexpr[i][j].substr(1))));
			}
			else if (rtexpr[i][j] == "?") {
				iscondition = true;
			}
		}
		if (isword(rtexpr[i][0][0])) {
			function fucexpr = functran(rtexpr[i]);	
			result.push_back(funccalc(fucexpr));
		}
		else if (iscondition) {
			string temp;
			if (stoi(rtexpr[i][0])) {
				temp = rtexpr[i][2];
			}
			else {
				temp = rtexpr[i][4];
			}
			result.push_back(stof(temp));
		}
		else {
			vector <string> expexpr = exprtran(rtexpr[i]);
			result.push_back(exprcalc(expexpr));
		}
	}
	return result.back();
}

extern "C" LIBRNPCALC_API double calculate(const char* expr) {
	return calculate(string(expr));
}
vector<string> pretreat(string expr) {
	ReplaceAll(expr, "PI", "3.1415926535898");
	ReplaceAll(expr, "E", "2.718281828459");
	ReplaceAll(expr, "rand()", to_string(rand()));
	for (int i = 0; i < expr.length(); ++i) {
		if (expr[i] == '-') {
			if (i != 0 ? !isnum(expr[i - 1]) : true)
			{
				if (!isnum(expr[i + 1])) {
					expr.insert(i, 1, '0');
				}
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
			if (expr[i] == '-') {
				if (i != 0 ? !iswordornum(expr[i - 1]) && expr[i - 1] != ')' : true) {
					if (!op_temp.empty()) {
						result_item.push_back(op_temp);
						op_temp.clear();
					}
					nm_temp.push_back(expr[i]);
				}
				else {
					if (!nm_temp.empty()) {
						result_item.push_back(nm_temp);
						nm_temp.clear();
					}
					op_temp.push_back(expr[i]);
				}
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
			k = i + 1;
			temp.clear();
		}
	}
	for (auto iter = result.params.begin(); iter != result.params.end(); ++iter) {
		*iter = exprtran(*iter);
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
		if (regex_match(expr[i],regex("-?\\d+(?:\\.\\d+)?|\\$\\d+")))
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

double exprcalc(vector<string> expr)
{
	stack<double> t_stack;
	for (int i = 0; i < expr.size(); i++)
	{
		if (regex_match(expr[i], regex("-?\\d+(?:\\.\\d+)?")))
		{
			t_stack.push(atof(expr[i].c_str()));
		}
		else
		{
			double a = t_stack.top();
			t_stack.pop();
			double b = 0;
			if (expr[i] != "!" && expr[i] != "~") {
				b = t_stack.top();
				t_stack.pop();
			}
			if (expr[i] == "+")t_stack.push(b + a);
			else if (expr[i] == "-")t_stack.push(b - a);
			else if (expr[i] == "*")t_stack.push(b * a);
			else if (expr[i] == "/")t_stack.push(b / a);
			else if (expr[i] == "%")t_stack.push((int)b % (int)a);
			else if (expr[i] == "!")t_stack.push(!a);
			else if (expr[i] == "&&")t_stack.push(b && a);
			else if (expr[i] == "||")t_stack.push(b || a);
			else if (expr[i] == "==")t_stack.push(b == a);
			else if (expr[i] == ">")t_stack.push(b > a);
			else if (expr[i] == "<")t_stack.push(b < a);
			else if (expr[i] == ">=")t_stack.push(b >= a);
			else if (expr[i] == "<=")t_stack.push(b <= a);
			else if (expr[i] == "!=")t_stack.push(b != a);
			else if (expr[i] == "&")t_stack.push((int)b & (int)a);
			else if (expr[i] == "|")t_stack.push((int)b | (int)a);
			else if (expr[i] == "^")t_stack.push((int)b ^ (int)a);
			else if (expr[i] == "~")t_stack.push(~(int)a);
			else if (expr[i] == "<<")t_stack.push((int)b << (int)a);
			else if (expr[i] == ">>")t_stack.push((int)b >> (int)a);
		}
	}
	return t_stack.top();
}

double funccalc(function expr) {
	vector<double> params;
	for (vector<string> i : expr.params) {
		params.push_back(exprcalc(i));
	}
	if (expr.name == "max") return max(params[0], params[1]);
	if (expr.name == "min") return min(params[0], params[1]);
	if (expr.name == "rand") return rand();
	if (expr.name == "randint") return randint((int)params[0], (int)params[1]);
	if (expr.name == "abs") return abs(params[0]);
	if (expr.name == "cos") return cos(params[0]);
	if (expr.name == "sin") return sin(params[0]);
	if (expr.name == "tan") return tan(params[0]);
	if (expr.name == "acos") return acos(params[0]);
	if (expr.name == "asin") return asin(params[0]);
	if (expr.name == "atan") return atan(params[0]);
	if (expr.name == "atan2") return atan2(params[0], params[1]);
	if (expr.name == "acosh") return acosh(params[0]);
	if (expr.name == "asinh") return asinh(params[0]);
	if (expr.name == "atanh") return atanh(params[0]);
	if (expr.name == "exp") return exp(params[0]);
	if (expr.name == "frexp") return frexp(params[0], (int*)&params[1]);
	if (expr.name == "ldexp") return ldexp(params[0], (int)params[1]);
	if (expr.name == "log") return log(params[0]);
	if (expr.name == "log10") return log10(params[0]);
	if (expr.name == "modf") return modf(params[0], &params[1]);
	if (expr.name == "exp2") return exp2(params[0]);
	if (expr.name == "expm1") return expm1(params[0]);
	if (expr.name == "ilogb") return ilogb(params[0]);
	if (expr.name == "log1p") return log1p(params[0]);
	if (expr.name == "log2") return log2(params[0]);
	if (expr.name == "logb") return logb(params[0]);
	if (expr.name == "logab") return log(params[1]) / log(params[0]);
	if (expr.name == "scalbn") return scalbn(params[0], (int)params[1]);
	if (expr.name == "scalbln") return scalbln(params[0], (long)params[1]);
	if (expr.name == "pow") return pow(params[0], params[1]);
	if (expr.name == "sqrt") return sqrt(params[0]);
	if (expr.name == "cbrt") return cbrt(params[0]);
	if (expr.name == "hypot") return hypot(params[0], params[1]);
	if (expr.name == "erf") return erf(params[0]);
	if (expr.name == "erfc") return erfc(params[0]);
	if (expr.name == "tgamma") return tgamma(params[0]);
	if (expr.name == "lgamma") return lgamma(params[0]);
	if (expr.name == "ceil") return ceil(params[0]);
	if (expr.name == "floor") return floor(params[0]);
	if (expr.name == "fmod") return fmod(params[0], params[1]);
	if (expr.name == "trunc") return trunc(params[0]);
	if (expr.name == "round") return round(params[0]);
	if (expr.name == "lround") return lround(params[0]);
	if (expr.name == "llround") return llround(params[0]);
	if (expr.name == "rint") return rint(params[0]);
	if (expr.name == "lrint") return lrint(params[0]);
	if (expr.name == "llrint") return llrint(params[0]);
	if (expr.name == "nearbyint") return nearbyint(params[0]);
	if (expr.name == "remainder") return remainder(params[0], params[1]);
	if (expr.name == "remquo") return remquo(params[0], params[1], (int*)&params[2]);
	if (expr.name == "copysign") return copysign(params[0], params[1]);
	if (expr.name == "nan") {
		char* str = (char*)malloc(INT16_MAX * sizeof(char));
		sprintf_s(str, INT16_MAX, "%lf", params[0]);
		double result = nan(str);
		free(str);
		return result;
	}
	if (expr.name == "nextafter") return nextafter(params[0], params[1]);
	if (expr.name == "nexttoward") return nexttoward(params[0], params[1]);
	if(expr.name=="fdim") return fdim(params[0], params[1]);
	if (expr.name == "fmax") return fmax(params[0], params[1]);
	if (expr.name == "fmin") return fmin(params[0], params[1]);
	if (expr.name == "fabs") return fabs(params[0]);
	if (expr.name == "fma") return fma(params[0], params[1], params[2]);
	if (expr.name == "fpclassify") return fpclassify(params[0]);
	if (expr.name == "isfinite") return isfinite(params[0]);
	if (expr.name == "isinf") return isinf(params[0]);
	if (expr.name == "isnan") return isnan(params[0]);
	if (expr.name == "isnormal") return isnormal(params[0]);
	if (expr.name == "signbit") return signbit(params[0]);
	if (expr.name == "isgreater") return isgreater(params[0], params[1]);
	if (expr.name == "isgreaterequal") return isgreaterequal(params[0], params[1]);
	if (expr.name == "isless") return isless(params[0], params[1]);
	if (expr.name == "islessequal") return islessequal(params[0], params[1]);
	if (expr.name == "islessgreater") return islessgreater(params[0], params[1]);
	if (expr.name == "isunordered") return isunordered(params[0], params[1]);
}
