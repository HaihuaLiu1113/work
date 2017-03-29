#include <iostream>
#include <string>
#include <string/iegad_string.hpp>


int main()
{
	std::string str("12345678");
	iegad::string_ex::start_with(str, '8');
	return 0;

}

