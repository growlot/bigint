#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <fstream>
#include <iostream>
#include "bigint.h"

int main(int argc, char **argv)
{
	// test1
	{
		bigint a("100000000");
		std::cout << "bigint a(\"100000000\") - " << a.to_string(true) << std::endl;
	}

	// test2
	{
		bigint b(100);
		std::cout << "bigint a(100) - " << b.to_string(true) << std::endl;
	}

	// test3
	{
		std::ofstream defaultfile("infile.txt");
		if(defaultfile.is_open())
		{
			defaultfile << "2000000000";
			defaultfile.close();
		}
		else std::cerr << "Unable to create default file" << std::endl;
		std::ifstream infile ("infile.txt");
		if(infile.is_open())
		{
			bigint c(infile);
			std::cout << "bigint a(infile) - " << c.to_string(true) << std::endl;
			infile.close();
		}
		else std::cerr << "Unable to open default file" << std::endl;
	}

	// test4
	{
		bigint a(0);
		bigint b(a);
		std::cout << "bigint b(a) - " << b.to_string(true) << std::endl;
	}

	// test5
	{
		bigint a = 1000000;
		std::cout << "a.to_string() - " << a.to_string() << std::endl; // prints "1000000\n"
		std::cout << "a.to_string(true) - " << a.to_string(true) << std::endl; // prints "1,000,000\n"
	}

	// test6
	{
		std::ofstream defaultfile("infile.txt");
		bigint a = "-10000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
		if(defaultfile.is_open())
		{
			a.to_file(defaultfile);
			defaultfile.close();
		}
		else std::cerr << "Unable to create default file" << std::endl;
		std::ifstream infile ("infile.txt");
		if(infile.is_open())
		{
			std::cout << "a.to_file(file) - " << std::endl << infile.rdbuf() << std::endl;
			infile.close();
		}
		else std::cerr << "Unable to open default file" << std::endl;
	}

	// test7
	{
		bigint a("00010");
		std::cout << "strip_zeros() of 00010 - " << a.to_string() << std::endl;
	}

	// test7
	{
		bigint a(123);
		unsigned int x = a[2];
		std::cout << "a[2] - " << x << std::endl;
	}

	// test8
	{
		bigint a(10);
		bigint b(10);
		std::cout << "a == b - " << (a == b ? "True" : "False") << ", a != b - " << (a != b ? "False" : "True") << std::endl;
	}

	// test9
	{
		bigint x = 10;
		bigint y = 15;
		bigint z = x.add(y);
		std::cout << "add x - " << x.to_string() << ", y - " << y.to_string() << ", z - " << z.to_string() << std::endl;
	}

	// test10
	{
		bigint x = 500;
		bigint y = 800;
		try
		{
			bigint z = x.subtract(y);
		}
		catch(const std::exception& e)
		{
			std::cerr << "x.subtract(y) - " << e.what() << std::endl;
		}
		try
		{
			bigint z = y.subtract(x);
			std::cout << "subtract x - " << x.to_string() << ", y - " << y.to_string() << ", z - " << z.to_string() << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << "y.subtract(x) - " << e.what() << std::endl;
		}
	}

	//test11
	{
		bigint x = 5;
		bigint y = 2;
		bigint z = x.multiply(y);
		std::cout << "multiply x - " << x.to_string() << ", y - " << y.to_string() << ", z - " << z.to_string() << std::endl;
	}

	return 0;
}
