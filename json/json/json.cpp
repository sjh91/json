// Sam Hardy
//sjh91@uakron.edu

#include "stdafx.h"
#include <cctype>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>
#include <iterator>
#include <map>


//Classes
struct Value
{
	virtual ~Value() = default;
	virtual void parse(std::string::iterator  & First, std::vector<std::unique_ptr<Value>> &v, int & weight) {}
};

struct Null :Value
{
	Null() = default;

	virtual void parse(std::string::iterator   & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
		int temp = v.size() + 1;
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
		if (* First == 't') 
		{
			int temp = v.size() + 1;
			v.resize(temp);
			v[temp].reset(new Bool(true));
			First + 4;
			++weight;
		}
		else if (*First == 'f')
		{
			int temp = v.size() + 1;
			v.resize(temp);
			v[temp].reset(new Bool(false));
			First + 5;
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
		Number x;
		while (isdigit(*First))
		{
			x.Num = *First;
			++First;
			if (*First == '.')
			{
				++First; //?
			}
		}


		double temp = v.size() + 1;
		v.resize(temp);
		v[temp].reset(new Number());
		++weight;
	}

};

struct String :Value, std::string
{
	using std::string::string;
	virtual void parse(std::string::iterator  & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
		String text;
		while (*First != '\"')
		{
			text += *First;
			++First;
		}


		int temp = v.size() + 1;
		v.resize(temp);
		v[temp].reset(new String());
		++weight;
	}


};

struct Array : Value, std::vector<Value *>
{
	Array() = default;
	~Array()
	{
		for (Value * v : *this)
			delete this;
	}
	using std::vector<Value *>::push_back;

	virtual void parse(std::string::iterator  & First, std::vector<std::unique_ptr<Value>> &v, int & weight)
	{
	
		while (*First != ']')
		{
			Array * a = new Array();
			int temp = v.size() + 1;
			v.resize(temp);
			v.at(temp).reset(a); //?
			++weight;
		}
	}

};
struct Object : Value, std::map<std::string, Value *> 
{
	using std::map<std::string, Value *>::map;
	using std::map<std::string, Value *>::insert;

	virtual void parse(std::string::iterator &First, std::vector<std::unique_ptr<Value>> &v, int &weight)
	{
		while (*First != '}')
		{
			int temp = v.size() + 1;
			v.resize(temp);
			v[temp].reset(new Object());
			++First;
			++weight;
		}
	}
};
// functions
void skip(std::string::iterator & First, std::string::iterator & Last)
{
	while (First != Last && std::isspace(*First))
		++First;
}
void doParse(std::string::iterator  & First, std::string::iterator & Last, std::vector<std::unique_ptr<Value>> & v, int & weight) {
	while (First != Last)
	{
		skip(First, Last);

		if (*First == 'n') {
			Null temp;
			temp.parse(First, v, weight);
			return;
		}

		else if (*First == 't' || *First == 'f') {
			Bool temp;
			temp.parse(First, v, weight);
			return;
		}

		else if (*First == '"') {
			String temp;
			temp.parse(First, v, weight);
			return;
		}

		else if (isdigit(*First)) {
			Number temp;
			temp.parse(First, v, weight);
			return;
		}

		else if (*First == '[') {
			Array temp;
			temp.parse(First, v, weight);
			return;
		}

		else if (*First == '{') {
			Object temp;
			temp.parse(First, v, weight);
			return;
		}
	}
}
int main()
{
	int weight = 0; // base weight
	std::string fileName;
	std::vector<std::unique_ptr<Value>> v; // holds json objects

	std::cout << "Enter json text file";
	std::cin >> fileName;
	std::ifstream file(fileName);
	
	
	std::string text{ std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>() };
	std::string::iterator First = text.begin();
	std::string::iterator Last = text.end();
	
	//parse
	doParse(First, Last,  v, weight);
	//cout weight
	std::cout << "weight = " << weight;
	
}
