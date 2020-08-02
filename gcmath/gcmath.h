#pragma once
#ifndef GCMATH_H_
#define GCMATH_H_
#include <cmath>
#include <string>
#include <iostream>
#include <vector>
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
typedef int BOOL;
typedef unsigned char BYTE;
typedef unsigned int UINT;
typedef int INT;
typedef unsigned long ULONG;
typedef long LONG;
typedef unsigned long long ULLONG;
typedef long long LLONG;
typedef double DOUBLE;
typedef long double LDOUBLE;
typedef float FLOAT;

class gcnum 
{
public:
	gcnum();
	gcnum(UINT val);
	gcnum(INT val);
	gcnum(ULONG val);
	gcnum(LONG val);
	gcnum(ULLONG val);
	gcnum(LLONG val);
	gcnum(DOUBLE val);
	gcnum(LDOUBLE val);
	gcnum(FLOAT val);
	gcnum(const std::string& val);
	gcnum(const char* val);
	std::string getstr();
	const char* getcstr();
	const double getnum();

	bool operator==(const gcnum& val);
	bool operator!=(const gcnum& val);
	bool operator<(const gcnum& val);
	bool operator>(const gcnum& val);
	bool operator<=(const gcnum& val);
	bool operator>=(const gcnum& val);

	gcnum operator+(const gcnum& val);
	gcnum operator-(const gcnum& val);
	gcnum operator*(const gcnum& val);
	gcnum operator/(const gcnum& val);
	gcnum operator%(const gcnum& val);

	gcnum operator-();

	gcnum& operator+=(const gcnum& val);
	gcnum& operator-=(const gcnum& val);
	gcnum& operator*=(const gcnum& val);
	gcnum& operator/=(const gcnum& val);
	gcnum& operator%=(const gcnum& val);
	gcnum& operator++();
	gcnum& operator++(int);

	bool operator==(const double& val);
	bool operator!=(const double& val);
	bool operator<(const double& val);
	bool operator>(const double& val);
	bool operator<=(const double& val);
	bool operator>=(const double& val);

	gcnum operator+(const double& val);
	gcnum operator-(const double& val);
	gcnum operator*(const double& val);
	gcnum operator/(const double& val);
	gcnum operator%(const double& val);

	gcnum& operator+=(const double& val);
	gcnum& operator-=(const double& val);
	gcnum& operator*=(const double& val);
	gcnum& operator/=(const double& val);
	gcnum& operator%=(const double& val);

	bool operator==(const int& val);
	bool operator!=(const int& val);
	bool operator<(const int& val);
	bool operator>(const int& val);
	bool operator<=(const int& val);
	bool operator>=(const int& val);

	gcnum operator+(const int& val);
	gcnum operator-(const int& val);
	gcnum operator*(const int& val);
	gcnum operator/(const int& val);
	gcnum operator%(const int& val);

	gcnum& operator+=(const int& val);
	gcnum& operator-=(const int& val);
	gcnum& operator*=(const int& val);
	gcnum& operator/=(const int& val);
	gcnum& operator%=(const int& val);

	gcnum& operator=(const UINT& val);
	gcnum& operator=(const INT& val);
	gcnum& operator=(const ULONG& val);
	gcnum& operator=(const LONG& val);
	gcnum& operator=(const ULLONG& val);
	gcnum& operator=(const LLONG& val);
	gcnum& operator=(const DOUBLE& val);
	gcnum& operator=(const LDOUBLE& val);
	gcnum& operator=(const FLOAT& val);
	gcnum& operator=(const std::string& val);
	gcnum& operator=(const char* val);
	gcnum& operator=(const char& val);
	gcnum& operator=(const BYTE& val);

	friend std::istream& operator>>(std::istream& in, gcnum& obj);
	friend std::ostream& operator<<(std::ostream& out, gcnum obj);

private:
	static int compare(const gcnum& a, const gcnum& b);
	static void INTADD(const gcnum& a, const gcnum& b, gcnum& result);
	static void INTSUB(const gcnum& a, const gcnum& b, gcnum& result);
	void GCDIV(const gcnum& val, gcnum& quo, gcnum& rem);
	void GCMUL(const gcnum& val, gcnum& result);
	static LLONG Dvalue(const LLONG& a, const LLONG& b);
	std::vector<BYTE> Data;
	int sign = 0;
	ULLONG decimals = 0;
};

#endif



