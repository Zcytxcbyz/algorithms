#ifdef LIBGCMATH_EXPORTS
#define LIBGCMATH_API __declspec(dllexport)
#else
#define LIBGCMATH_API __declspec(dllimport)
#endif
#include <cmath>
#include <string>
#include <vector>
const auto PI = 3.1415926535898;
const auto E = 2.718281828459;
#define max(a,b) (((a) > (b)) ? (a) : (b))
#define min(a,b) (((a) < (b)) ? (a) : (b))
LIBGCMATH_API typedef int BOOL;
LIBGCMATH_API typedef unsigned char BYTE;
LIBGCMATH_API typedef unsigned int UINT;
LIBGCMATH_API typedef int INT;
LIBGCMATH_API typedef unsigned long ULONG;
LIBGCMATH_API typedef long LONG;
LIBGCMATH_API typedef unsigned long long ULLONG;
LIBGCMATH_API typedef long long LLONG;
LIBGCMATH_API typedef double DOUBLE;
LIBGCMATH_API typedef long double LDOUBLE;
LIBGCMATH_API typedef float FLOAT;
extern LIBGCMATH_API UINT GCMath_Accuracy;
extern LIBGCMATH_API BOOL GCMath_Mulmode;
class gcnum
{
public:	
	LIBGCMATH_API gcnum();
	LIBGCMATH_API ~gcnum();
	LIBGCMATH_API gcnum(UINT val);
	LIBGCMATH_API gcnum(INT val);
	LIBGCMATH_API gcnum(ULONG val);
	LIBGCMATH_API gcnum(LONG val);
	LIBGCMATH_API gcnum(ULLONG val);
	LIBGCMATH_API gcnum(LLONG val);
	LIBGCMATH_API gcnum(DOUBLE val);
	LIBGCMATH_API gcnum(LDOUBLE val);
	LIBGCMATH_API gcnum(FLOAT val);
	LIBGCMATH_API gcnum(const std::string& val);
	LIBGCMATH_API gcnum(const char* val);
	LIBGCMATH_API std::string getstr();
	LIBGCMATH_API const char* getcstr();
	LIBGCMATH_API const LDOUBLE getnum();
	LIBGCMATH_API const ULLONG getdeclen();
	LIBGCMATH_API const ULLONG getintlen();
	LIBGCMATH_API const int* getdata();

	LIBGCMATH_API bool operator==(const gcnum& val);
	LIBGCMATH_API bool operator!=(const gcnum& val);
	LIBGCMATH_API bool operator<(const gcnum& val);
	LIBGCMATH_API bool operator>(const gcnum& val);
	LIBGCMATH_API bool operator<=(const gcnum& val);
	LIBGCMATH_API bool operator>=(const gcnum& val);

	LIBGCMATH_API gcnum operator+(const gcnum& val);
	LIBGCMATH_API gcnum operator-(const gcnum& val);
	LIBGCMATH_API gcnum operator*(const gcnum& val);
	LIBGCMATH_API gcnum operator/(const gcnum& val);
	LIBGCMATH_API gcnum operator%(const gcnum& val);

	LIBGCMATH_API gcnum operator-();

	LIBGCMATH_API gcnum& operator+=(const gcnum& val);
	LIBGCMATH_API gcnum& operator-=(const gcnum& val);
	LIBGCMATH_API gcnum& operator*=(const gcnum& val);
	LIBGCMATH_API gcnum& operator/=(const gcnum& val);
	LIBGCMATH_API gcnum& operator%=(const gcnum& val);
	LIBGCMATH_API gcnum& operator++();
	LIBGCMATH_API gcnum& operator++(int);
	LIBGCMATH_API gcnum& operator--();
	LIBGCMATH_API gcnum& operator--(int);

	LIBGCMATH_API bool operator==(const double& val);
	LIBGCMATH_API bool operator!=(const double& val);
	LIBGCMATH_API bool operator<(const double& val);
	LIBGCMATH_API bool operator>(const double& val);
	LIBGCMATH_API bool operator<=(const double& val);
	LIBGCMATH_API bool operator>=(const double& val);

	LIBGCMATH_API gcnum operator+(const double& val);
	LIBGCMATH_API gcnum operator-(const double& val);
	LIBGCMATH_API gcnum operator*(const double& val);
	LIBGCMATH_API gcnum operator/(const double& val);
	LIBGCMATH_API gcnum operator%(const double& val);

	LIBGCMATH_API gcnum& operator+=(const double& val);
	LIBGCMATH_API gcnum& operator-=(const double& val);
	LIBGCMATH_API gcnum& operator*=(const double& val);
	LIBGCMATH_API gcnum& operator/=(const double& val);
	LIBGCMATH_API gcnum& operator%=(const double& val);

	LIBGCMATH_API bool operator==(const int& val);
	LIBGCMATH_API bool operator!=(const int& val);
	LIBGCMATH_API bool operator<(const int& val);
	LIBGCMATH_API bool operator>(const int& val);
	LIBGCMATH_API bool operator<=(const int& val);
	LIBGCMATH_API bool operator>=(const int& val);

	LIBGCMATH_API gcnum operator+(const int& val);
	LIBGCMATH_API gcnum operator-(const int& val);
	LIBGCMATH_API gcnum operator*(const int& val);
	LIBGCMATH_API gcnum operator/(const int& val);
	LIBGCMATH_API gcnum operator%(const int& val);

	LIBGCMATH_API gcnum& operator+=(const int& val);
	LIBGCMATH_API gcnum& operator-=(const int& val);
	LIBGCMATH_API gcnum& operator*=(const int& val);
	LIBGCMATH_API gcnum& operator/=(const int& val);
	LIBGCMATH_API gcnum& operator%=(const int& val);

	LIBGCMATH_API gcnum& operator=(const UINT& val);
	LIBGCMATH_API gcnum& operator=(const INT& val);
	LIBGCMATH_API gcnum& operator=(const ULONG& val);
	LIBGCMATH_API gcnum& operator=(const LONG& val);
	LIBGCMATH_API gcnum& operator=(const ULLONG& val);
	LIBGCMATH_API gcnum& operator=(const LLONG& val);
	LIBGCMATH_API gcnum& operator=(const DOUBLE& val);
	LIBGCMATH_API gcnum& operator=(const LDOUBLE& val);
	LIBGCMATH_API gcnum& operator=(const FLOAT& val);
	LIBGCMATH_API gcnum& operator=(const std::string& val);
	LIBGCMATH_API gcnum& operator=(const char* val);
	LIBGCMATH_API gcnum& operator=(const char& val);
	LIBGCMATH_API gcnum& operator=(const BYTE& val);

	LIBGCMATH_API gcnum& operator>>(const int& val);
	LIBGCMATH_API gcnum& operator<<(const int& val);

	LIBGCMATH_API friend std::istream& operator>>(std::istream& in, gcnum& obj);
	LIBGCMATH_API friend std::ostream& operator<<(std::ostream& out, gcnum obj);

	LIBGCMATH_API friend std::ifstream& operator>>(std::ifstream& in, gcnum& obj);
	LIBGCMATH_API friend std::ofstream& operator<<(std::ofstream& out, gcnum& obj);

	LIBGCMATH_API friend gcnum operator+(const double& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator-(const double& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator*(const double& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator/(const double& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator%(const double& a, const gcnum& b);

	LIBGCMATH_API friend bool operator==(const double& a, const gcnum& b);
	LIBGCMATH_API friend bool operator!=(const double& a, const gcnum& b);
	LIBGCMATH_API friend bool operator<(const double& a, const gcnum& b);
	LIBGCMATH_API friend bool operator>(const double& a, const gcnum& b);
	LIBGCMATH_API friend bool operator<=(const double& a, const gcnum& b);
	LIBGCMATH_API friend bool operator>=(const double& a, const gcnum& b);

	LIBGCMATH_API friend gcnum operator+(const int& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator-(const int& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator*(const int& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator/(const int& a, const gcnum& b);
	LIBGCMATH_API friend gcnum operator%(const int& a, const gcnum& b);

	LIBGCMATH_API friend bool operator==(const int& a, const gcnum& b);
	LIBGCMATH_API friend bool operator!=(const int& a, const gcnum& b);
	LIBGCMATH_API friend bool operator<(const int& a, const gcnum& b);
	LIBGCMATH_API friend bool operator>(const int& a, const gcnum& b);
	LIBGCMATH_API friend bool operator<=(const int& a, const gcnum& b);
	LIBGCMATH_API friend bool operator>=(const int& a, const gcnum& b);

	LIBGCMATH_API friend gcnum abs(gcnum _X);
	LIBGCMATH_API friend gcnum ceil(gcnum _X);
	LIBGCMATH_API friend gcnum floor(gcnum _X);
	LIBGCMATH_API friend gcnum round(gcnum _X);

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
	void INTDIV(const gcnum& val, gcnum& quo, gcnum& rem);
	inline void karatsuba(const gcnum& a, const gcnum& b, gcnum& result);
	gcnum karatsuba(const gcnum& a, const gcnum& b, int xa, int xb, int ya, int yb);
	gcnum karatmul(const gcnum& a, const gcnum& b, int xa, int xb, int ya, int yb);
	inline int getkaralen(int x, int y);
};




