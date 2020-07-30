#ifndef PERSON_H
#define PERSON_H
#include <string>

int StrToInt32(std::string str)
{
	int result = 0, pos = 1;
	for (int i = str.length() - 1; i >= 0; i--)
	{
		result += (str[i] - '0') * pos;
		pos *= 10;
	}
	return result;
}

std::string Int32ToStr(int number)
{
	std::string result;
	while (number > 0) 
	{
		result = (char)(number % 10 + '0') + result;
		number /= 10;
	}
	return result;
}

int GetNumLength(int num) 
{
	int i = 0;
	while (num > 0) 
	{
		num /= 10;
		i++;
	}
	return i;
}
#endif
