#include <fstream>
#include <iostream>
#include "framework.h"
#include "gcmath.h"
#define GCNUMTYPE std::vector<BYTE>
#define ITER iterator
#define CITER const_iterator
#define GCITER GCNUMTYPE::ITER
#define GCCITER GCNUMTYPE::CITER
LIBGCMATH_API UINT GCMath_Accuracy = 500;

gcnum::gcnum(){ }

gcnum::gcnum(UINT val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(INT val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(ULONG val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(LONG val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(ULLONG val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(LLONG val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(DOUBLE val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(LDOUBLE val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(FLOAT val)
{
	std::string str = std::to_string(val);
	*this = gcnum(str);
}

gcnum::gcnum(const std::string& val)
{
	for (int i = val.length() - 1; i >= 0; --i) {
		if (val[i] == '-') {
			sign = 1;
		}
		else if (val[i] == '.') {
			decimals = (int)val.length() - i - 1;
		}
		else {
			Data.push_back(val[i] - '0');
		}
	}
	this->correct();
}

gcnum::gcnum(const char* val)
{
	for (int i = strlen(val) - 1; i >= 0; --i) {
		if (val[i] == '-') {
			sign = 1;
		}
		else if (val[i] == '.') {
			decimals = strlen(val) - i - 1;
		}
		else {
			gcnum::Data.push_back(val[i] - '0');
		}
	}
	this->correct();
}

std::string gcnum::getstr()
{
	std::string result;
	for (int i = 0; i < Data.size(); ++i) {
		if (i == decimals && decimals > 0) result = '.' + result;
		result = (char)(Data[i] + '0') + result;
	}
	if (sign)result = '-' + result;
	return result;
}

const char* gcnum::getcstr()
{
	int length = Data.size() + 1;
	if (sign) ++length;
	if (decimals > 0) ++length;
	char* result = (char*)malloc(length * sizeof(char));
	result[length - 1] = '\0';
	for (int i = 0, j = Data.size() - 1; i < length && j >= 0; ++i, --j) {
		if (sign && i == 0) 
		{
			result[0] = '-';
			++i;
		}
		if (i == length - decimals - 2 && decimals > 0) {
			result[i] = '.';
			++i;
		}
		result[i] = Data[j] + '0';
	}
	return result;
}
const LDOUBLE gcnum::getnum()
{
	LDOUBLE result = 0;
	ULLONG cpt = 1;
	for (auto item : this->Data) {
		result += (LDOUBLE)item * cpt;
		cpt *= 10;
	}
	for (int i = 0; i < this->decimals; ++i) {
		result /= 10;
	}
	return result;
}
const ULLONG gcnum::getdeclen()
{
	return this->decimals;
}
const ULLONG gcnum::getintlen()
{
	return (ULLONG)this->Data.size() - this->decimals;
}
const int* gcnum::getdata()
{
	int length = this->Data.size() + 2;
	int* result = new int[length];
	for (int i = 0, j = 0; i < length && j < Data.size(); ++i, ++j)
	{
		if (i == 0) result[i] = this->sign;
		else if(i == 1) result[i] = this->decimals;
		else result[i] = this->Data[j];
	}
	return result;
}
int gcnum::compare(const gcnum& a, const gcnum& b)
{
	if (a.sign && !b.sign) return -1;
	if (!a.sign && b.sign) return 1;
	int alength = a.Data.size() - a.decimals;
	int blength = b.Data.size() - b.decimals;
	if (alength < blength) return -1;
	if (alength > blength) return 1;
	for (int i = a.Data.size() - 1, j = b.Data.size() - 1; i >= a.decimals && j >= b.decimals; --i, --j) {
		if (a.Data[i] < b.Data[j]) return -1;
		if (a.Data[i] > b.Data[j]) return 1;
	}
	for (int i = a.decimals - 1, j = b.decimals - 1; i >= 0 && j >= 0; --i, --j) {
		if (a.Data[i] < b.Data[j]) return -1;
		if (a.Data[i] > b.Data[j]) return 1;
	}
	if (a.decimals == b.decimals) return 0;
	if (a.decimals < b.decimals) return -1;
	if (a.decimals > b.decimals) return 1;
}

int gcnum::divcompare(const gcnum& a, const gcnum& b)
{
	if (a.Data.size() < b.Data.size()) return -1;
	if (a.Data.size() > b.Data.size()) return 1;
	for (int i = a.Data.size() - 1, j = b.Data.size() - 1; i >= 0 && j >= 0; --i, --j) {
		if (a.Data[i] < b.Data[j]) return -1;
		if (a.Data[i] > b.Data[j]) return 1;
	}
	return 0;
}

bool gcnum::operator==(const gcnum& val)
{
	return compare(*this, val) == 0;
}
bool gcnum::operator!=(const gcnum& val)
{
	return compare(*this, val) != 0;
}
bool gcnum::operator<(const gcnum& val)
{
	return compare(*this, val) == -1;
}
bool gcnum::operator>(const gcnum& val)
{
	return compare(*this, val) == 1;
}
bool gcnum::operator<=(const gcnum& val)
{
	return compare(*this, val) <= 0;
}
bool gcnum::operator>=(const gcnum& val)
{
	return compare(*this, val) >= 0;
}
gcnum gcnum::operator+(const gcnum& val)
{
	gcnum result;
	const gcnum* lnum = this;
	const gcnum* rnum = &val;
	if (lnum->sign ^ rnum->sign){
		if (lnum->sign) {
			gcnum left = *lnum;
			gcnum right = *rnum;
			left.sign = 0;
			return right - left;
		}
		if (rnum->sign) {
			gcnum left = *lnum;
			gcnum right = *rnum;
			right.sign = 0;
			return left - right;
		}
	}
	if (lnum->sign && rnum->sign) result.sign = 1;
	int temp, carry = 0;
	int alength = lnum->Data.size() - lnum->decimals;
	int blength = rnum->Data.size() - rnum->decimals;
	int mlnum = max(alength, blength) + max(lnum->decimals, rnum->decimals);
	result.decimals = max(lnum->decimals, rnum->decimals);
	int n = Dvalue(lnum->decimals, rnum->decimals);
	const gcnum* sdectnum = lnum->decimals <= rnum->decimals ? lnum : rnum;
	const gcnum* ldectnum = lnum->decimals > rnum->decimals ? lnum : rnum;
	for (int i = 0; i < mlnum; ++i) {
		if (i < n) {
			temp = ldectnum->Data[i];
		}
		else if (i > sdectnum->Data.size() + n - 1) {
			temp = ldectnum->Data[i] + carry;
			carry = 0;
		}
		else if (i > ldectnum->Data.size() - 1) {
			temp = sdectnum->Data[i - n] + carry;
			carry = 0;
		}
		else {
			temp = lnum->Data[lnum == sdectnum ? i - n : i] + rnum->Data[rnum == sdectnum ? i - n : i] + carry;
			if (temp >= 10) {
				temp -= 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
		}	
		result.Data.push_back(temp);
	}
	if (carry > 0) result.Data.push_back(carry);
	result.correct();
	return result;
}
gcnum gcnum::operator-(const gcnum& val)
{
	gcnum result;
	const gcnum* lnum = this;
	const gcnum* rnum = &val;
	if (lnum->sign ^ rnum->sign) {
		if (lnum->sign){
			gcnum left = *lnum;
			gcnum right = *rnum;
			left.sign = 0;
			return -(left + right);
		}
		if (rnum->sign){
			gcnum left = *lnum;
			gcnum right = *rnum;
			right.sign = 0;
			return left + right;
		}
	}
	if (lnum->sign && rnum->sign) {
		gcnum left = *lnum;
		gcnum right = *rnum;
		left.sign = 0;
		right.sign = 0;
		return right - left;
	}
	switch (compare(*lnum, *rnum))
	{
		case -1:
			std::swap(lnum, rnum); 
			result.sign = 1; 
			break;
		case 0:
			return gcnum(0);
	}
	int temp, carry = 0;
	int alength = lnum->Data.size() - lnum->decimals;
	int blength = rnum->Data.size() - rnum->decimals;
	result.decimals = max(lnum->decimals, rnum->decimals);
	int mlnum =  max(alength, blength) + max(lnum->decimals, rnum->decimals);
	int n = Dvalue(lnum->decimals, rnum->decimals);
	const gcnum* sdectnum = lnum->decimals <= rnum->decimals ? lnum : rnum;
	const gcnum* ldectnum = lnum->decimals > rnum->decimals ? lnum : rnum;
	for (int i = 0; i < mlnum; ++i) {
		if (i < n) {
			temp = 10 - ldectnum->Data[i];
			carry = 1;
		}
		else if (i > sdectnum->Data.size() + n - 1) {
			temp = ldectnum->Data[i] - carry;
			carry = 0;
		}
		else if (i > ldectnum->Data.size() - 1) {
			temp = sdectnum->Data[i - n] - carry;
			carry = 0;
		}
		else {
			temp = lnum->Data[lnum == sdectnum ? i - n : i] - rnum->Data[rnum == sdectnum ? i - n : i] - carry;
			if (temp < 0) {
				temp += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
		}
		result.Data.push_back(temp);
	}
	result.correct();
	return result;
}
gcnum gcnum::operator*(const gcnum& val)
{
	gcnum result;
	const gcnum* lnum = this;
	const gcnum* rnum = &val;
	if (lnum->sign ^ rnum->sign) result.sign = 1;
	if (lnum->Data.size() < rnum->Data.size())std::swap(lnum, rnum);
	result.decimals = lnum->decimals + rnum->decimals;
	SMAMUL(*lnum, *rnum, result);
	result.correct();
	return result;
}
gcnum gcnum::operator/(const gcnum& val)
{
	int n = 0;
	if (GCMath_Accuracy > this->decimals) {
		n = GCMath_Accuracy - this->decimals;
	}
	gcnum lnum = *this;
	gcnum rnum = val;
	gcnum rem, qtemp1, qtemp2, temp, quo;
	int pox = lnum.decimals + rnum.decimals;
	lnum << pox;
	rnum << pox;
	lnum.INTDIV(rnum, qtemp1, rem);
	rem << n;
	rem.INTDIV(rnum, qtemp2, temp);
	qtemp2 >> n;
	for (int i = 0; i < qtemp2.decimals && i < qtemp2.Data.size(); ++i) {
		quo.Data.push_back(qtemp2.Data[i]);
	}
	for (int i = 0; i < qtemp1.Data.size(); ++i) {
		quo.Data.push_back(qtemp1.Data[i]);
	}
	quo.decimals = qtemp2.decimals;
	if (this->sign ^ val.sign) quo.sign = 1;
	return quo;
}
gcnum gcnum::operator%(const gcnum& val)
{
	gcnum lnum = *this;
	gcnum rnum = val;
	for (int i = 0; i < lnum.decimals; ++i) {
		lnum.Data.erase(lnum.Data.begin());
	}
	for (int i = 0; i < rnum.decimals; ++i) {
		rnum.Data.erase(rnum.Data.begin());
	}
	lnum.decimals = 0; rnum.decimals = 0;
	gcnum quo, rem;
	lnum.INTDIV(rnum, quo, rem);
	if (this->sign) rem.sign = 1;
	rem.correct();
	return rem;
}

void gcnum::INTDIV(const gcnum& val, gcnum& quo, gcnum& rem)
{
	gcnum lnum = *this;
	gcnum rnum = val;
	quo.Data.push_back(0);
	if (divcompare(lnum, rnum) == -1) {
		rem = lnum; return;
	}
	int pox = Dvalue(lnum.Data.size(), rnum.Data.size());
	rnum.LEFTMOVE(pox); 
	do
	{
		while (pox > 0 && divcompare(lnum, rnum) == -1) {
			--pox; 
			rnum.Data.erase(rnum.Data.begin());
		}
		lnum = INTSUB(lnum, rnum);
		quo = INTADD(quo, ELMOVE(pox));
	} while (divcompare(lnum, val) >= 0);
	rem = lnum;
}

gcnum gcnum::ELMOVE(const int& val)
{
	gcnum result;
	for (int i = 0; i < val; ++i) {
		result.Data.push_back(0);
	}
	result.Data.push_back(1);
	return result;
}

gcnum& gcnum::LEFTMOVE(const int& val)
{
	for (int i = 0; i < val; ++i) {
		this->Data.insert(this->Data.begin(), 0);
	}
	return *this;
}

gcnum& gcnum::RIGHTMOVE(const int& val)
{
	for (int i = 0; i < val; ++i) {
		this->Data.erase(this->Data.begin());
	}
	return *this;
}

void gcnum::SMAMUL(const gcnum& BNUM, const gcnum& SNUM, gcnum& result)
{
	int temp, carry = 0;
	for (int j = 0; j < SNUM.Data.size(); ++j) {
		for (int i = 0; i < BNUM.Data.size(); ++i) {
			temp = SNUM.Data[j] * BNUM.Data[i] + carry;
			carry = temp / 10;
			temp %= 10;
			if ((i + j) >= result.Data.size()) {
				result.Data.push_back(temp);
			}
			else {
				result.Data[i + j] += temp;
				carry += result.Data[i + j] / 10;
				result.Data[i + j] %= 10;
			}
		}
		if (carry > 0)result.Data.push_back(carry);
		carry = 0;
	}
}

gcnum& gcnum::operator>>(const int& val) 
{
	for (int i = 0; i < val; ++i) {
		++(this->decimals);
	}
	this->correct();
	return *this;
}

gcnum& gcnum::operator<<(const int& val) 
{
	for (int i = 0; i < val; ++i) {
		if (this->decimals > 0) --(this->decimals);
		else this->Data.insert(this->Data.begin(), 0);	
	}
	this->correct();
	return *this;
}

gcnum& gcnum::operator++()
{
	*this = (*this) + gcnum(1);
	return *this;
}

gcnum& gcnum::operator++(int)
{
	gcnum temp = *this;
	*this = (*this) + gcnum(1);
	return temp;
}

gcnum& gcnum::operator--()
{
	*this = (*this) - gcnum(1);
	return *this;
}

gcnum& gcnum::operator--(int)
{
	gcnum temp = *this;
	*this = (*this) - gcnum(1);
	return temp;
}

int gcnum::Dvalue(const int& a, const int& b)
{
	return a > b ? a - b : b - a;
}

void gcnum::correct()
{
	if ((this->Data.size() == 1) && (this->Data[0] == 0)) {
		this->decimals = 0; this->sign = 0;
		return;
	}
	for (int i = this->Data.size() - 1; i >= decimals; --i) {
		if (this->Data[i] == 0) this->Data.pop_back();
		else break;
	}
	while (this->decimals > 0){
		if (*(this->Data.begin()) == 0){
			this->Data.erase(this->Data.begin());
			--(this->decimals);
		}
		else break;
	}
	while (this->decimals >= this->Data.size())
	{
		this->Data.push_back(0);
	}
}

void gcnum::divcorrect()
{
	if ((this->Data.size() == 1) && (this->Data[0] == 0))return;
	for (int i = this->Data.size() - 1; i >= decimals; --i) {
		if (this->Data[i] == 0) this->Data.pop_back();
		else break;
	}
}

gcnum gcnum::INTADD(const gcnum& a, const gcnum& b)
{
	gcnum result;
	int temp, carry = 0;
	int mlnum = max(a.Data.size(), b.Data.size());
	const gcnum* sintnum = a.Data.size() <= b.Data.size() ? &a : &b;
	const gcnum* lintnum = a.Data.size() > b.Data.size() ? &a : &b;
	for (int i = 0; i < mlnum; ++i) {
		if (i > sintnum->Data.size() - 1) {
			temp = lintnum->Data[i] + carry;
			carry = 0;
		}
		else {
			temp = a.Data[i] + b.Data[i] + carry;
			if (temp >= 10) {
				temp -= 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
		}
		result.Data.push_back(temp);
	}
	if (carry > 0) result.Data.push_back(carry);
	return result;
}

gcnum gcnum::INTSUB(const gcnum& a, const gcnum& b)
{
	gcnum result;
	int temp, carry = 0;
	int mlnum = max(a.Data.size(), b.Data.size());
	const gcnum* sintnum = a.Data.size() <= b.Data.size() ? &a : &b;
	const gcnum* lintnum = a.Data.size() > b.Data.size() ? &a : &b;
	for (int i = 0; i < mlnum; ++i) {
		if (i > sintnum->Data.size() - 1) {
			temp = lintnum->Data[i] - carry;
			carry = 0;
		}
		else {
			temp = a.Data[i] - b.Data[i] - carry;
			if (temp < 0) {
				temp += 10;
				carry = 1;
			}
			else {
				carry = 0;
			}
		}
		result.Data.push_back(temp);
	}
	for (int i = result.Data.size() - 1; i >= 0; --i) {
		if (result.Data[i] == 0) result.Data.pop_back();
		else break;
	}
	return result;
}

gcnum gcnum::operator-()
{
	this->sign = !this->sign;
	return *this;
}

gcnum& gcnum::operator+=(const gcnum& val)
{
	*this = (*this) + val;
	return *this;
}

gcnum& gcnum::operator-=(const gcnum& val)
{
	*this = (*this) - val;
	return *this;
}

gcnum& gcnum::operator*=(const gcnum& val)
{
	*this = (*this) * val;
	return *this;
}

gcnum& gcnum::operator/=(const gcnum& val)
{
	*this = (*this) / val;
	return *this;
}

gcnum& gcnum::operator%=(const gcnum& val)
{
	*this = (*this) % val;
	return *this;
}

bool gcnum::operator==(const double& val) {
	return (*this) == gcnum(val);
}

bool gcnum::operator!=(const double& val) {
	return (*this) != gcnum(val);
}

bool gcnum::operator<(const double& val) {
	return (*this) < gcnum(val);
}
bool gcnum::operator>(const double& val) {
	return (*this) > gcnum(val);
}
bool gcnum::operator<=(const double& val) {
	return (*this) <= gcnum(val);
}
bool gcnum::operator>=(const double& val) {
	return (*this) >= gcnum(val);
}

gcnum gcnum::operator+(const double& val) {
	return (*this) + gcnum(val);
}
gcnum gcnum::operator-(const double& val) {
	return (*this) - gcnum(val);
}
gcnum gcnum::operator*(const double& val) {
	return (*this) * gcnum(val);
}
gcnum gcnum::operator/(const double& val) {
	return (*this) / gcnum(val);
}
gcnum gcnum::operator%(const double& val) {
	return (*this) % gcnum(val);
}

gcnum& gcnum::operator+=(const double& val) {
	return (*this) += gcnum(val);
}
gcnum& gcnum::operator-=(const double& val) {
	return (*this) -= gcnum(val);
}
gcnum& gcnum::operator*=(const double& val) {
	return (*this) *= gcnum(val);
}
gcnum& gcnum::operator/=(const double& val) {
	return (*this) /= gcnum(val);
}
gcnum& gcnum::operator%=(const double& val) {
	return (*this) %= gcnum(val);
}

bool gcnum::operator==(const int& val) {
	return (*this) == gcnum(val);
}
bool gcnum::operator!=(const int& val) {
	return (*this) != gcnum(val);
}
bool gcnum::operator<(const int& val) {
	return (*this) < gcnum(val);
}
bool gcnum::operator>(const int& val) {
	return (*this) > gcnum(val);
}
bool gcnum::operator<=(const int& val) {
	return (*this) <= gcnum(val);
}
bool gcnum::operator>=(const int& val) {
	return (*this) >= gcnum(val);
}

gcnum gcnum::operator+(const int& val) {
	return (*this) + gcnum(val);
}
gcnum gcnum::operator-(const int& val) {
	return (*this) - gcnum(val);
}
gcnum gcnum::operator*(const int& val) {
	return (*this) * gcnum(val);
}
gcnum gcnum::operator/(const int& val) {
	return (*this) / gcnum(val);
}
gcnum gcnum::operator%(const int& val) {
	return (*this) % gcnum(val);
}

gcnum& gcnum::operator+=(const int& val) {
	return (*this) += gcnum(val);
}
gcnum& gcnum::operator-=(const int& val) {
	return (*this) -= gcnum(val);
}
gcnum& gcnum::operator*=(const int& val) {
	return (*this) *= gcnum(val);
}
gcnum& gcnum::operator/=(const int& val) {
	return (*this) /= gcnum(val);
}
gcnum& gcnum::operator%=(const int& val) {
	return (*this) %= gcnum(val);
}

std::istream& operator>>(std::istream& in, gcnum& obj)
{
	std::string val;
	in >> val;
	for (int i = val.length() - 1; i >= 0; --i) {
		if (val[i] == '-') {
			obj.sign = 1;
		}
		else if (val[i] == '.') {
			obj.decimals = val.length() - i - 1;
		}
		else {
			obj.Data.push_back(val[i] - '0');
		}
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, gcnum obj)
{
	if (obj.sign) out << "-";
	for (int i = obj.Data.size() - 1, j = 0; i >= 0; --i, ++j) {
		if (j == obj.Data.size() - obj.decimals && obj.decimals > 0) 
		{
			out << ".";
		}
		out << (char)(obj.Data[i] + '0');
	}
	return out;
}

std::ifstream& operator>>(std::ifstream& in, gcnum& obj)
{
	std::string val;
	in >> val;
	for (int i = val.length() - 1; i >= 0; --i) {
		if (val[i] == '-') {
			obj.sign = 1;
		}
		else if (val[i] == '.') {
			obj.decimals = val.length() - i - 1;
		}
		else {
			obj.Data.push_back(val[i] - '0');
		}
	}
	return in;
}

std::ofstream& operator<<(std::ofstream& out, gcnum& obj)
{
	if (obj.sign) out << "-";
	for (int i = obj.Data.size() - 1, j = 0; i >= 0; --i, ++j) {
		if (j == obj.Data.size() - obj.decimals && obj.decimals > 0)
		{
			out << ".";
		}
		out << (char)(obj.Data[i] + '0');
	}
	return out;
}

gcnum gcnum::GETINTDEC(INTDECMODE mode)
{
	gcnum result; result.sign = this->sign;
	if (decimals == 0) return *this;
	for (int i = decimals; i < Data.size(); ++i) {
		result.Data.push_back(Data[i]);
	}
	if (mode == INTDECMODE::CEIL) {
		if (!sign) ++result;
	}
	else if (mode == INTDECMODE::FLOOR) {
		if (sign) --result;
	}
	else if (mode == INTDECMODE::ROUND) {
		int nnump = Data[decimals - 1];
		if (sign)result -= (nnump >= 5 ? 1 : 0);
		else result += (nnump >= 5 ? 1 : 0);
	}
	return result;
}

gcnum abs(gcnum _X)
{
	if (_X.sign == 1) _X.sign = 0;
	return _X;
}

gcnum ceil(gcnum _X)
{
	return _X.GETINTDEC(gcnum::INTDECMODE::CEIL);
}

gcnum floor(gcnum _X)
{
	return _X.GETINTDEC(gcnum::INTDECMODE::FLOOR);
}

gcnum round(gcnum _X)
{
	return _X.GETINTDEC(gcnum::INTDECMODE::ROUND);
}


gcnum& gcnum::operator=(const UINT& val)
{
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const INT& val)
{
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const ULONG& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const LONG& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const ULLONG& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const LLONG& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const DOUBLE& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const LDOUBLE& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const FLOAT& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const std::string& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const char* val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const char& val) {
	*this = gcnum(val); 
	return *this;
}
gcnum& gcnum::operator=(const BYTE& val) {
	*this = gcnum(val); 
	return *this;
}

gcnum operator+(const double& a, const gcnum& b) {
	return gcnum(a) + b;
}
gcnum operator-(const double& a, const gcnum& b) {
	return gcnum(a) - b;
}
gcnum operator*(const double& a, const gcnum& b) {
	return gcnum(a) * b;
}
gcnum operator/(const double& a, const gcnum& b) {
	return gcnum(a) / b;
}
gcnum operator%(const double& a, const gcnum& b) {
	return gcnum(a) % b;
}
 
bool operator==(const double& a, const gcnum& b) {
	return gcnum(a) == b;
}
bool operator!=(const double& a, const gcnum& b) {
	return gcnum(a) != b;
}
bool operator<(const double& a, const gcnum& b) {
	return gcnum(a) < b;
}
bool operator>(const double& a, const gcnum& b) {
	return gcnum(a) > b;
}
bool operator<=(const double& a, const gcnum& b) {
	return gcnum(a) <= b;
}
bool operator>=(const double& a, const gcnum& b) {
	return gcnum(a) >= b;
}

gcnum operator+(const int& a, const gcnum& b) {
	return gcnum(a) + b;
}
gcnum operator-(const int& a, const gcnum& b) {
	return gcnum(a) - b;
}
gcnum operator*(const int& a, const gcnum& b) {
	return gcnum(a) * b;
}
gcnum operator/(const int& a, const gcnum& b) {
	return gcnum(a) / b;
}
gcnum operator%(const int& a, const gcnum& b) {
	return gcnum(a) % b;
}

bool operator==(const int& a, const gcnum& b) {
	return gcnum(a) == b;
}
bool operator!=(const int& a, const gcnum& b) {
	return gcnum(a) != b;
}
bool operator<(const int& a, const gcnum& b) {
	return gcnum(a) < b;
}
bool operator>(const int& a, const gcnum& b) {
	return gcnum(a) > b;
}
bool operator<=(const int& a, const gcnum& b) {
	return gcnum(a) <= b;
}
bool operator>=(const int& a, const gcnum& b) {
	return gcnum(a) >= b;
}
