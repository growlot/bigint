#ifndef BIGINT_H
#define BIGINT_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <functional>
#include "bigint.h"
#define MAX 10000 // for strings

using namespace std;

///// Constructors /////

bigint::bigint()
{
	_number = "0";
	_sign = false;
}

bigint::bigint(const char * s)
{
	*this = bigint(string(s));
}

bigint::bigint(const string &s)
{
	if( isdigit(s[0]) ) // if not signed
	{
		set_number(s);
		_sign = false; // +ve
	}
	else
	{
		set_number( s.substr(1) );
		_sign = (s[0] == '-');
	}
}

bigint::bigint(const string &s, bool sin)
{
	set_number( s );
	set_sign( sin );
}

bigint::bigint(short n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(unsigned short n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(int n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(unsigned int n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(long long n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(unsigned long long n)
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;

	set(s);
}

bigint::bigint(const istream &stream)
{
	ostringstream os;
	os << stream.rdbuf();
	string s(os.str());
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
	set(s);
}

///////////////////////////////////

void bigint::set(const string &s)
{
	if( isdigit(s[0]) ) // if not signed
	{
		set_number( s );
		set_sign( false ); // +ve
	}
	else
	{
		set_number( s.substr(1) );
		set_sign( s[0] == '-' );
	}
}

void bigint::set_number(const string &s)
{
	_number = s;
	strip_zeros();
}

const string& bigint::get_number() const // retrieves the number
{
	return _number;
}

void bigint::strip_zeros()
{
	ltrim(_number, '0');
}

void bigint::set_sign(bool s)
{
	_sign = s;
}

const bool& bigint::get_sign() const
{
	return _sign;
}

// returns the absolute value
bigint bigint::absolute() const
{
	return bigint( get_number() ); // +ve by default
}

void bigint::operator = (const bigint &b)
{
	set_number( b.get_number() );
	set_sign( b.get_sign() );
}

bool bigint::operator == (const bigint &b) const
{
	return equals((*this) , b);
}

bool bigint::operator != (const bigint &b) const
{
	return ! equals((*this) , b);
}

bool bigint::operator > (const bigint &b) const
{
	return greater((*this) , b);
}

bool bigint::operator < (const bigint &b) const
{
	return less((*this) , b);
}

bool bigint::operator >= (const bigint &b) const
{
	return equals((*this) , b)
		|| greater((*this), b);
}

bool bigint::operator <= (const bigint &b) const
{
	return equals((*this) , b) 
		|| less((*this) , b);
}

// increments the value, then returns its value
bigint& bigint::operator ++() // prefix
{
	(*this) = (*this) + 1;
	return (*this);
}

// returns the value, then increments its value
bigint bigint::operator ++(int) // postfix
{
	bigint before = (*this);

	(*this) = (*this) + 1;

	return before;
}

// decrements the value, then return it
bigint& bigint::operator --() // prefix
{
	(*this) = (*this) - 1;
	return (*this);

}

// return the value, then decrements it
bigint bigint::operator --(int) // postfix
{	
	bigint before = (*this);

	(*this) = (*this) - 1;

	return before;
}

bigint bigint::operator + (const bigint &b) const
{
	bigint addition;
	if( get_sign() == b.get_sign() ) // both +ve or -ve
	{
		addition.set_number( add(get_number(), b.get_number() ) );
		addition.set_sign( get_sign() );
	}
	else // sign different
	{
		if( absolute() > b.absolute() )
		{
			addition.set_number( subtract(get_number(), b.get_number() ) );
			addition.set_sign( get_sign() );
		}
		else
		{
			addition.set_number( subtract(b.get_number(), get_number() ) );
			addition.set_sign( b.get_sign() );
		}
	}
	if(addition.get_number() == "0") // avoid (-0) problem
		addition.set_sign(false);

	return addition;
}

bigint bigint::operator - (const bigint &b) const
{
	bigint b1(b);
	b1.set_sign( ! b1.get_sign() ); // x - y = x + (-y)
	return (*this) + b1;
}

bigint bigint::operator * (const bigint &b) const
{
	bigint mul;

	mul.set_number( multiply(get_number(), b.get_number() ) );
	mul.set_sign( get_sign() != b.get_sign() );

	if(mul.get_number() == "0") // avoid (-0) problem
		mul.set_sign(false);

	return mul;
}

// Warning: Denomerator must be within "long long" size not "bigint"
bigint bigint::operator / (const bigint &b) const
{
	long long den = to_int( b.get_number() );
	bigint div;

	div.set_number( divide(get_number(), den).first );
	div.set_sign( get_sign() != b.get_sign() );

	if(div.get_number() == "0") // avoid (-0) problem
		div.set_sign(false);

	return div;
}

// Warning: Denomerator must be within "long long" size not "bigint"
bigint bigint::operator % (const bigint &b) const
{
	long long den = to_int( b.get_number() );

	bigint rem;
	long long rem_int = divide(_number, den).second;
	rem.set_number( to_string(rem_int) );
	rem.set_sign( get_sign() != b.get_sign() );

	if(rem.get_number() == "0") // avoid (-0) problem
		rem.set_sign(false);

	return rem;
}

bigint& bigint::operator += (const bigint &b)
{
	(*this) = (*this) + b;
	return (*this);
}

bigint& bigint::operator -= (const bigint &b)
{
	(*this) = (*this) - b;
	return (*this);
}

bigint& bigint::operator *= (const bigint &b)
{
	(*this) = (*this) * b;
	return (*this);
}

bigint& bigint::operator /= (const bigint &b)
{
	(*this) = (*this) / b;
	return (*this);
}

bigint& bigint::operator %= (const bigint &b)
{
	(*this) = (*this) % b;
	return (*this);
}

unsigned int bigint::operator [] (unsigned int n) const
{
	return n < strlen(_number.c_str()) ?
		(_number[n - 1] - '0') :
		0;
}

bigint bigint::operator -() // unary minus sign
{
	return (*this) * -1;
}

bigint::operator string() const // for conversion from bigint to string
{
	return to_string();
}

string bigint::to_string(bool commas) const
{
	std::string resultStr;
	if(commas)
	{
		unsigned int len = strlen(_number.c_str());
		unsigned int offset = len % 3;
		for(unsigned int i = 0; i < len; ++i)
		{
			if(i % 3 == offset && i)
				resultStr += ',';
			resultStr += _number.at(i);
		}
	}
	else
	{
		resultStr = _number;
	}

	string signedString = ( get_sign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += resultStr;
	return signedString;
}

void bigint::to_file(ostream &stream, unsigned int wrap) const
{
	std::string resultStr;
	unsigned int len = strlen(_number.c_str());
	unsigned int offset = 0;
	for(unsigned int i = 0; i < len; ++i)
	{
		if(i % wrap == offset && i)
			resultStr += '\n';
		resultStr += _number.at(i);
	}

	string signedString = ( get_sign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += resultStr;

	stream << signedString;
}

string bigint::scientific(unsigned int decimal_points)
{
	string resultStr(_number);
	unsigned int len = strlen(_number.c_str());
	if(len <= decimal_points)
	{
		unsigned int tmp = decimal_points - len + 1;
		resultStr.insert(0, tmp, '0');
		len += tmp;
	}
	resultStr.insert(len - decimal_points, 1, '.');
	rtrim(resultStr, '0');

	string signedString = ( get_sign() ) ? "-" : ""; // if +ve, don't print + sign
	
	stringstream ss;
	ss << signedString << resultStr << "e+" << decimal_points;

	return ss.str();
}

bigint bigint::add(const bigint &n) const
{
	return *this + n;
}

bigint bigint::subtract(const bigint &n) const
{
	if (*this < n)
		throw std::runtime_error("NOT ALLOWED - could not subtract bigger one.");

	return *this - n;
}

bigint bigint::multiply(const bigint &n) const
{
	return *this * n;
}

bool bigint::equals(const bigint &n1, const bigint &n2)
{
	return n1.get_number() == n2.get_number()
		&& n1.get_sign() == n2.get_sign();
}

bool bigint::less(const bigint &n1, const bigint &n2)
{
	bool sign1 = n1.get_sign();
	bool sign2 = n2.get_sign();

	if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1) // both +ve
	{
		if(n1.get_number().length() < n2.get_number().length() )
			return true;
		if(n1.get_number().length() > n2.get_number().length() )
			return false;
		return n1.get_number() < n2.get_number();
	}
	else // both -ve
	{
		if(n1.get_number().length() > n2.get_number().length())
			return true;
		if(n1.get_number().length() < n2.get_number().length())
			return false;
		return n1.get_number().compare( n2.get_number() ) > 0; // greater with -ve sign is LESS
	}
}

bool bigint::greater(const bigint &n1, const bigint &n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}

// adds two strings and returns their sum in as a string
string bigint::add(const string &n1, const string &n2)
{
	string tn1(n1);
	string tn2(n2);

	string add = (tn1.length() > n2.length()) ?  tn1 : n2;
	char carry = '0';
	int differenceInLength = abs( (int) (tn1.size() - tn2.size()) );

	if(tn1.size() > tn2.size())
		tn2.insert(0, differenceInLength, '0'); // put zeros from left
	else// if(tn1.size() < tn2.size())
		tn1.insert(0, differenceInLength, '0');

	for(int i=tn1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(tn1[i]-'0')+(tn2[i]-'0')) + '0';

		if(i != 0)
		{	
			if(add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if(add[0] > '9')
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

// subtracts two strings and returns their sum in as a string
string bigint::subtract(const string &n1, const string &n2)
{
	string tn1(n1);
	string tn2(n2);

	string sub = (tn1.length()>tn2.length())? tn1 : tn2;
	int differenceInLength = abs( (int)(tn1.size() - tn2.size()) );

	if(tn1.size() > tn2.size())	
		tn2.insert(0, differenceInLength, '0');
	else
		tn1.insert(0, differenceInLength, '0');

	for(int i=tn1.length()-1; i>=0; --i)
	{
		if(tn1[i] < tn2[i])
		{
			tn1[i] += 10;
			tn1[i-1]--;
		}
		sub[i] = ((tn1[i]-'0')-(tn2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1) // erase leading zeros
		sub.erase(0,1);

	return sub;
}

// multiplies two strings and returns their sum in as a string
string bigint::multiply(const string &n1, const string &n2)
{
	string tn1(n1);
	string tn2(n2);

	if(tn1.length() > tn2.length()) 
		tn1.swap(tn2);

	string res = "0";
	for(int i=tn1.length()-1; i>=0; --i)
	{
		string temp = tn2;
		int currentDigit = tn1[i]-'0';
		int carry = 0;

		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;

			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((tn1.length()-i-1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp); // O(n)
	}

	while(res[0] == '0' && res.length()!=1) // erase leading zeros
		res.erase(0,1);

	return res;
}

// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> bigint::divide(const string &n, long long den)
{
	long long rem = 0;
	string result; result.resize(MAX);
	
	for(int indx=0, len = n.length(); indx<len; ++indx)
	{
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

// converts long long to string
string bigint::to_string(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

// converts string to long long
long long bigint::to_int(const string &s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}

void bigint::ltrim(string& s, char c)
{
   if(s.empty())
      return;

   string::iterator p;
   for (p = s.begin(); p != s.end() && *p == c; p++);

   s.erase(s.begin(), p);
}

void bigint::rtrim(string& s, char c) {

   if(s.empty())
      return;

   string::iterator p;
   for (p = s.end(); p != s.begin() && *--p == c;);

   if (*p != c)
      p++;

   s.erase(p, s.end());
}

#endif
