#include "gcmath.h"

gcnum::gcnum(){ }

gcnum::gcnum(UINT val)
{
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(INT val)
{
	if (val < 0) {
		sign = 1;
		val = abs(val);
	}
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(ULONG val)
{
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(LONG val)
{
	if (val < 0) {
		sign = 1;
		val = abs(val);
	}
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(ULLONG val)
{
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(LLONG val)
{
	if (val < 0) {
		sign = 1;
		val = abs(val);
	}
	while (val > 0) {
		Data.push_back(val % 10);
		val /= 10;
	}
}

gcnum::gcnum(DOUBLE val)
{
	LDOUBLE lval = val;
	if (lval < 0) {
		sign = 1;
		lval = abs(lval);
	}
	while (floor(lval) != lval)
	{
		lval *= 10;
		++decimals;
	}
	ULLONG temp = lval;
	while (temp > 0) {
		Data.push_back(temp % 10);
		temp /= 10;
	}
}

gcnum::gcnum(LDOUBLE val)
{
	if (val < 0) {
		sign = 1;
		val = abs(val);
	}
	while (floor(val) != val)
	{
		val *= 10;
		++decimals;
	}
	ULLONG temp = val;
	while (temp > 0) {
		Data.push_back(temp % 10);
		temp /= 10;
	}
}

gcnum::gcnum(FLOAT val)
{
	LDOUBLE lval = val;
	if (lval < 0) {
		sign = 1;
		lval = abs(lval);
	}
	while (floor(lval) != lval)
	{
		lval *= 10;
		++decimals;
	}
	ULLONG temp = lval;
	while (temp > 0) {
		Data.push_back(temp % 10);
		temp /= 10;
	}
}

gcnum::gcnum(const std::string& val)
{
	for (LLONG i = val.length() - 1; i >= 0; --i) {
		if (val[i] == '-') {
			sign = 1;
		}
		else if (val[i] == '.') {
			decimals = val.length() - i - 1;
		}
		else {
			gcnum::Data.push_back(val[i] - '0');
		}
	}
}

gcnum::gcnum(const char* val)
{
	for (LLONG i = strlen(val) - 1; i >= 0; --i) {
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
}

std::string gcnum::getstr()
{
	std::string result;
	for (LLONG i = 0; i < Data.size(); ++i) {
		if (i == decimals && decimals > 0) result = '.' + result;
		result = (char)(Data[i] + '0') + result;
	}
	if (sign)result = '-' + result;
	return result;
}

const char* gcnum::getcstr()
{
	LONG length = Data.size() + 1;
	if (sign) ++length;
	if (decimals > 0) ++length;
	char* result = (char*)malloc(length * sizeof(char));
	result[length - 1] = '\0';
	for (LLONG i = 0, j = Data.size() - 1; i < length && j >= 0; ++i, --j) {
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
const double gcnum::getnum()
{
	return 0.0;
}
//a>b return 1,a<b return -1,a=b return 0
int gcnum::compare(const gcnum& a, const gcnum& b)
{
	if (a.sign && !b.sign) return -1;
	if (!a.sign && b.sign) return 1;
	LLONG alength = a.Data.size() - a.decimals;
	LLONG blength = b.Data.size() - b.decimals;
	if (alength < blength) return -1;
	if (alength > blength) return 1;
	for (LLONG i = a.Data.size() - 1, j = b.Data.size() - 1; i >= a.decimals && j >= b.decimals; --i, --j) {
		if (a.Data[i] < b.Data[j]) return -1;
		if (a.Data[i] > b.Data[j]) return 1;
	}
	if (a.decimals < b.decimals) return -1;
	if (a.decimals > b.decimals) return 1;
	for (LLONG i = a.decimals - 1; i >= 0; --i) {
		if (a.Data[i] < b.Data[i]) return -1;
		if (a.Data[i] > b.Data[i]) return 1;
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
	LLONG alength = lnum->Data.size() - lnum->decimals;
	LLONG blength = rnum->Data.size() - rnum->decimals;
	LLONG mlnum = alength >= blength ? lnum->Data.size() : rnum->Data.size();
	result.decimals = max(lnum->decimals, rnum->decimals);
	LLONG n = Dvalue(lnum->decimals, rnum->decimals);
	const gcnum* sdectnum = lnum->decimals <= rnum->decimals ? lnum : rnum;
	const gcnum* ldectnum = lnum->decimals > rnum->decimals ? lnum : rnum;
	for (LLONG i = 0; i < mlnum; ++i) {
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
	if (compare(*lnum, *rnum) == -1) {
		std::swap(lnum, rnum);
		result.sign = 1;
	}
	int temp, carry = 0;
	LLONG alength = lnum->Data.size() - lnum->decimals;
	LLONG blength = rnum->Data.size() - rnum->decimals;
	result.decimals = max(lnum->decimals, rnum->decimals);
	LLONG mlnum = alength >= blength ? lnum->Data.size() : rnum->Data.size();
	LLONG n = Dvalue(lnum->decimals, rnum->decimals);
	const gcnum* sdectnum = lnum->decimals <= rnum->decimals ? lnum : rnum;
	const gcnum* ldectnum = lnum->decimals > rnum->decimals ? lnum : rnum;
	for (LLONG i = 0; i < mlnum; ++i) {
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
	for (LLONG i = result.Data.size() - 1; i >= 0; --i) {
		if (result.Data[i] == 0) result.Data.pop_back();
		else break;
	}
	return result;
}
gcnum gcnum::operator*(const gcnum& val)
{
	gcnum result;
	this->GCMUL(val, result);
	return result;
}
gcnum gcnum::operator/(const gcnum& val)
{
	gcnum quo, rem;
	this->GCDIV(val, quo, rem);
	return quo;
}
gcnum gcnum::operator%(const gcnum& val)
{
	gcnum quo, rem;
	this->GCDIV(val, quo, rem);
	return rem;
}

void gcnum::GCDIV(const gcnum& val, gcnum& quo, gcnum& rem)
{
	const gcnum* lnum = this;
	const gcnum* rnum = &val;
	quo = 1, rem = 1;
}

void gcnum::GCMUL(const gcnum& val, gcnum& result)
{
	const gcnum* lnum = this;
	const gcnum* rnum = &val;
	result = 1;
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

LLONG gcnum::Dvalue(const LLONG& a, const LLONG& b)
{
	return a > b ? a - b : b - a;
}

void gcnum::INTADD(const gcnum& a, const gcnum& b, gcnum& result)
{
	int temp, carry = 0;
	LLONG mlnum = max(a.Data.size(), b.Data.size());
	const gcnum* sintnum = a.Data.size() <= b.Data.size() ? &a : &b;
	const gcnum* lintnum = a.Data.size() > b.Data.size() ? &a : &b;
	for (LLONG i = 0; i < mlnum; ++i) {
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
}

void gcnum::INTSUB(const gcnum& a, const gcnum& b, gcnum& result)
{
	int temp, carry = 0;
	LLONG mlnum = max(a.Data.size(), b.Data.size());
	const gcnum* sintnum = a.Data.size() <= b.Data.size() ? &a : &b;
	const gcnum* lintnum = a.Data.size() > b.Data.size() ? &a : &b;
	for (LLONG i = 0; i < mlnum; ++i) {
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
	for (LLONG i = result.Data.size() - 1; i >= 0; --i) {
		if (result.Data[i] == 0) result.Data.pop_back();
		else break;
	}
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
	for (LLONG i = val.length() - 1; i >= 0; --i) {
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
	for (LLONG i = obj.Data.size() - 1, j = 0; i >= 0; --i, ++j) {
		if (j == obj.Data.size() - obj.decimals && obj.decimals > 0) 
		{
			out << ".";
		}
		out << (char)(obj.Data[i] + '0');
	}
	return out;
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
