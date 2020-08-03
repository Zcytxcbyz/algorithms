#pragma once
#ifndef GCMATH_H_
#define GCMATH_H_
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
constexpr auto PI = 3.1415926535898;
constexpr auto E = 2.718281828459;
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

struct {
	UINT accuracy = 100;
	BOOL mulmode = 0;
}GCMath_Setting;

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
	const LDOUBLE getnum();
	const ULLONG getdeclen();
	const ULLONG getintlen();
	const int* getdata();

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
	gcnum& operator--();
	gcnum& operator--(int);

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

	gcnum& operator>>(const int& val);
	gcnum& operator<<(const int& val);

	friend std::istream& operator>>(std::istream& in, gcnum& obj);
	friend std::ostream& operator<<(std::ostream& out, gcnum obj);

	friend std::ifstream& operator>>(std::ifstream& in, gcnum& obj);
	friend std::ofstream& operator<<(std::ofstream& out, gcnum& obj);

	friend gcnum abs(gcnum _X);
	friend gcnum ceil(gcnum _X);
	friend gcnum floor(gcnum _X);
	friend gcnum round(gcnum _X);
private:
	int sign = 0, decimals = 0;
	enum class INTDECMODE { CEIL, FLOOR, ROUND };
	gcnum GETINTDEC(INTDECMODE mode);
	gcnum& LEFTMOVE(const int& val);
	gcnum& RIGHTMOVE(const int& val);
	void correct();
	void divcorrect();
	std::vector<BYTE> Data;
	static int compare(const gcnum& a, const gcnum& b);
	static int divcompare(const gcnum& a, const gcnum& b);
	static gcnum INTADD(const gcnum& a, const gcnum& b);
	static gcnum INTSUB(const gcnum& a, const gcnum& b);
	static gcnum ELMOVE(const int& val);
	static void SMAMUL(const gcnum& BNUM, const gcnum& SNUM, gcnum& result);
	static int Dvalue(const int& a, const int& b);
	void GCMUL(const gcnum& val, gcnum& result);
	void INTDIV(const gcnum& val, gcnum& quo, gcnum& rem);
};

#endif



