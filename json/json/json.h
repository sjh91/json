
//#include <string>
#include <vector>

struct Value 
{
	virtual ~ Value() = default;
};

struct Null:Value
{};

struct Bool:Value
{
	Bool(bool B) : Value(B) {}
	bool Value;
};

struct Number:Value
{
	//Number(double N) : Value(N) {}
	double N;
};

struct String :Value,std::string
{
	using std::string::string;
};

