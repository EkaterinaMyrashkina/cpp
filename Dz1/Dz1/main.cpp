#include <iostream>
using namespace std;

class String
{
	unsigned size = 0;
	char *str = nullptr;
public:
	String(const char *s)
	{
		if (s&&*s)
		{
			size = strlen(s) + 1;
			str = new char[size];
			strcpy_s(str, size, s);
		}
	}
	void print()
	{
		cout << str << endl;
	}
	const char* get_str()
	{
		return str;
	}
	void assign(const char *s)
	{
		size = strlen(s) + 1;
		delete[]str;
		str = new char[size];
		strcpy_s(str, size, s);
	}
	void concat(const char *s)
	{
		size += strlen(s);
		char* new_str = new char[size];
		strcpy_s(new_str, size, str);
		strcat_s(new_str, size, s);
		delete[]str;
		str = new_str;
	}
	void transfer() //ASCII code
	{
		int number;
		for (unsigned i = 0; i < size - 1; ++i)
		{
			number = (int)str[i];
			cout << str[i] << "  ASCII code = " << number << endl;
		}
	}
	void BigLetter()
	{
		_strupr_s(str, size);
	}
	void SmallLetter()
	{
		_strlwr_s(str, size);
	}
	int Length()
	{
		return strlen(str);
	}
	void Insert(char symbol, unsigned pozition)
	{
		if (pozition < size && pozition>0)
		{
			++size;
			char * new_str = new char[size];
			for (unsigned i = 0; i < size; ++i)
			{
				if (i < pozition)
					new_str[i] = str[i];
				else if (i == pozition)
					new_str[i] = symbol;
				else
					new_str[i] = str[i - 1];
			}
			delete[]str;
			str = new_str;
		}
		else cout << "erroneous position" << endl;
	}
	~String()
	{
		if (str)
			delete[]str;
		str = nullptr;
	}
};
int main()
{
	String str = "Hello";
	str.print();
	str.assign("Hi");
	str.print();
	str.concat(" Worlds!");
	cout << str.get_str() << endl;
	str.BigLetter();
	cout << "high register: " << str.get_str() << endl;
	str.SmallLetter();
	cout << "low register: " << str.get_str() << endl;
	cout << "string length = " << str.Length() << endl;
	cout << "Insert of symbol:" << endl;
	str.Insert('a', 3);
	cout << str.get_str() << endl;
	cout << "ASCII code:" << endl;
	str.transfer();
}