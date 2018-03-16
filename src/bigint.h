#include <string>
#include <istream>
#define MAX 10000 // for strings

//-------------------------------------------------------------
class bigint
{
private:
	std::string _number;
	bool _sign;

public:
	bigint();
	bigint(const char *s);
	bigint(const std::string &s);
	bigint(const std::string &s, bool sin);
	bigint(short n);
	bigint(unsigned short n);
	bigint(int n);
	bigint(unsigned int n);
	bigint(long long n);
	bigint(unsigned long long n);
	bigint(const std::istream &stream);
	void set_sign(bool s);
	const bool& get_sign() const;
	bigint absolute() const; // returns the absolute value
	void operator = (const bigint &b);
	bool operator == (const bigint &b) const;
	bool operator != (const bigint &b) const;
	bool operator > (const bigint &b) const;
	bool operator < (const bigint &b) const;
	bool operator >= (const bigint &b) const;
	bool operator <= (const bigint &b) const;
	bigint& operator ++(); // prefix
	bigint operator ++(int); // postfix
	bigint& operator --(); // prefix
	bigint operator --(int); // postfix
	bigint operator + (const bigint &b) const;
	bigint operator - (const bigint &b) const;
	bigint operator * (const bigint &b) const;
	bigint operator / (const bigint &b) const;
	bigint operator % (const bigint &b) const;
	bigint& operator += (const bigint &b);
	bigint& operator -= (const bigint &b);
	bigint& operator *= (const bigint &b);
	bigint& operator /= (const bigint &b);
	bigint& operator %= (const bigint &b);
	unsigned int operator [] (unsigned int n) const;
	bigint operator -();
	operator std::string() const;

	std::string to_string(bool commas = false) const;
	void to_file(std::ostream &stream, unsigned int wrap = 80) const;
	std::string scientific(unsigned int decimal_points = 3);
	bigint add(const bigint &n) const;
	bigint subtract(const bigint &n) const;
	bigint multiply(const bigint &n) const;

private:
	void set(const std::string &s);
	void set_number(const std::string &s);
	const std::string& get_number() const;
	void strip_zeros();
	static bool equals(const bigint &n1, const bigint &n2);
	static bool less(const bigint &n1, const bigint &n2);
	static bool greater(const bigint &n1, const bigint &n2);
	static std::string add(const std::string &n1, const std::string &n2);
	static std::string subtract(const std::string &n1, const std::string &n2);
	static std::string multiply(const std::string &n1, const std::string &n2);
	static std::pair<std::string, long long> divide(const std::string &n, long long den);
	static std::string to_string(long long n);
	static long long to_int(const std::string &s);
	static void ltrim(std::string &s, char c);
	static void rtrim(std::string &s, char c);
};

