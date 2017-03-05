// json.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "json.h"
#include <stddef.h>
#include <iostream>


Value * Parce(char * & First, char * & Last) {
	while(First != Last && std::isspace(*First))
		++First;
	if (First == "T" || First == "t")
		Parce_true(First, Last);

	if (First == "F" || First == "f")
		Parce_false(First, Last);

	if (First == nullptr)
		Parce_false(First, Last);

	if (First == "[")
		Parce_array(First, Last);

	//if (First == """)
		//Parce_string(First, Last);
	if (First == "1"|| First == "2" || First == "3" || First == "4" || First == "5" || First == "6"|| First == "7" || First == "8" || First == "9");
		Parce_number(First, Last);
}
//Value * Parce_true(char * & f, char * &);
int main()
{
	
}
