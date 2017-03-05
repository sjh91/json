// json.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
//#include "json.h"
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <map>
struct Value
{
	virtual ~Value() = default;
	virtual void parse(std::string::iterator * & First, std::vector<std::unique_ptr<Value>> &v, int & weight);
};

struct Null :Value
{
	Null() = default;

	virtual void parse(std::string::iterator  * & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
		char temp = v.size() + 1;
		v.resize(temp);
		v[temp].reset(new Null());
		First + 4; //null
		++weight; // 1 to weight for null
	}

};

struct Bool :Value
{
	bool Val;
	Bool() = default;
	Bool(bool B) : Val(B) {}
	
	virtual void parse(std::string::iterator  & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
		if (* First == 'T') 
		{
			char temp = v.size() + 1;
			v.resize(temp);
			v[temp].reset(new Bool(true));
			First + 4;
			++weight;
		}
	}
};

struct Number :Value
{
	double Num;
	Number() = default;
	Number(double N) : Num(N) {}

	virtual void parse(std::string::iterator  & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
		char number;
		while (isdigit(*First))
		{


		}
	}
};

struct String :Value, std::string
{
	using std::string::string;
};

struct array :Value //std::vector<Value *>
{
	std::vector <Value*> Value;

	//~array()
	//{
	//for (Value:: this*)
	//{
	//delete this;
	//}

};
Value * Parce(char * & First, char * Last)
{
	while (First != Last && std::isspace(*First))
		++First;
}
int main()
{
	
}
