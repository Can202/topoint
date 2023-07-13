#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "string_functions.h"
using namespace std;

int main(){
	cout << keyword_in("if bla is bla do", "do") << "\n";
	cout << keyword_in("	print(\"Hola Mundo.\")", "print") << "\n";
	cout << str_starts_with("	print(\"Hola Mundo.\")", "print") << "\n";
	return 0;
}
