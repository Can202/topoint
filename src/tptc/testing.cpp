#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "string_functions.h"
using namespace std;

int main(){
	cout << keyword_in("if bla is bla do", "do") << "\n";
	cout << keyword_in("print(\"Hola Mundo do \")", "do") << "\n";
	return 0;
}
