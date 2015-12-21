using namespace std;
#include <iostream>

class DestrString  //передача прав
{
	unsigned size = 0;
	char* str = nullptr;
public:
	DestrString() = default;
	DestrString(const char* s)
	{
		if (s && *s)
		{
			size = strlen(s) + 1;
			str = new char[size];
			strcpy_s(str, size, s);
		}
	}
	DestrString(DestrString& obj)
	{
		if (str)
			delete str;
		size = obj.size;
		str = obj.str;
		obj.str = nullptr;
	}
	void PrintStr()
	{
		if (str)
			cout << str;
		else cout << "String is empty";
	}
	DestrString& operator=(DestrString& obj)
	{
		if (str)
			delete str;
		size = obj.size;
		str = obj.str;
		obj.str = nullptr;
	}
	~DestrString()
	{
		if (str)
			delete[] str;
		str = nullptr;
	}
	friend ostream& operator << (ostream& os, const DestrString& s);
};
ostream& operator << (ostream& os, const DestrString& s)
{
	os << s.str;
	return os;
}
class UniqueString //уникальный ресурс
{
	unsigned size = 0;
	char* str = nullptr;
public:
	UniqueString() = default;
	UniqueString(const char* s)
	{
		if (s && *s)
		{
			size = strlen(s) + 1;
			str = new char[size];
			strcpy_s(str, size, s);
		}
	}
	UniqueString(const UniqueString& obj) = delete;
	UniqueString& operator=(const UniqueString& obj) = delete;
	~UniqueString()
	{
		if (str)
			delete[] str;
		str = nullptr;
	}
	friend ostream& operator << (ostream& os, const UniqueString& s);
};
ostream& operator << (ostream& os, const UniqueString& s)
{
	os << s.str;
	return os;
}

struct resource
{
	unsigned count = 0;
	char* str = nullptr;
	unsigned size = 0;
};
class CoowerString  //совместное владение
{
	resource Res;
public:
	CoowerString() = default;
	CoowerString(const char* s)
	{
		if (s && *s)
		{
			Res.size = strlen(s) + 1;
			Res.str = new char[Res.size];
			strcpy_s(Res.str, Res.size, s);
			Res.count = 1;
		}
	}
	CoowerString(const CoowerString& obj)
	{
		if (Res.str)
			delete[] Res.str;
		Res.size = obj.Res.size;
		Res.str = obj.Res.str;
		Res.count = obj.Res.count;
		++Res.count;
	}
	void PrintStr()
	{
		if (Res.str)
			cout << Res.str;
		else cout << "String is empty";
	}
	~CoowerString()
	{
		--Res.count;
		if (Res.str && Res.count == 0)
			delete[] Res.str;
		Res.str = nullptr;
	}
	friend ostream& operator << (ostream& os, const CoowerString& s);
};
ostream& operator << (ostream& os, const CoowerString& s)
{
	os << s.Res.str;
	return os;
}
int main()
{
	/*Описать классы, реализующие RAII-обёртки(передача прав, уникальный ресурс,
	совместное владение) над ресурсом(ресурс может быть любой). Написать программу,
	демонстрирующую работу с этим классом. Программа должна содержать меню, позволяющее
	осуществить проверку всех методов классов.*/
	int select;
	while (true)
	{
		cout << "Select: " << endl;
		cout << "1 - Unique resource" << endl << "2 - Rights to the resource" << endl << "3 - Co-ownership of resource" << endl << "4 - exit" << endl;
		cin >> select;
		if (select == 1)
		{
			cout << "Unique resource" << endl;
			UniqueString u_str1("Hello");
			cout << "Str1 = " << u_str1 << endl;
			cout << "Trying create a new obj and initialization by Str1" << endl;
			cout << "Str2 = str1" << endl;
			cout << "function UniqueResource::UniqueResource(UniqueResource &res_) cannot be referenced -- it is a deleted function" << endl;
			cout << "Str2 = str1" << endl;
			cout << "Trying use operator = " << endl;
			cout << "function UniqueResource::operator=(const UniqueResource &res) cannot be referenced -- it is a deleted function" << endl;
		}
		else 
			if (select == 2)
			{
				cout << "Rights to the resource" << endl;
				DestrString d_str1("Hello");
				cout << "Str1 = " << d_str1 << endl;
				cout << "str2 = str1" << endl;
				DestrString d_str2 = d_str1;
				cout << "Str2 = " << d_str2 << endl;
				cout << "Resource str1 removed" << endl;
			}
			else 
				if (select == 3)
				{
					cout << "Co-ownership of resource" << endl;
					CoowerString c_str1("Hello");
					cout << "Str1 = " << c_str1 << endl;
					cout << "str2 = str1" << endl;
					CoowerString c_str2 = c_str1;
					cout << "Str1 = " << c_str1 << endl;
					cout << "str2 = " << c_str2 << endl;
				}
				else break;
	}
	return 0;
}