#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
int transform_code_to_cpp(string program_location, string output);
void write_text(string dir, string text);
string get_text_from_file(string dir);


int main (int argc, char* argv[]){
	
	
	if (argc != 0){
		string argv1(argv[1]);
		transform_code_to_cpp(argv1, "a.cpp");
	} else {
		while (true){
		
		}
	}
	
	return 0;
}

int transform_code_to_cpp(string program_location, string output){
	
	cout << get_text_from_file(program_location) << "\n";
		
	string text = "";
		
	return 0;
	
}

string get_text_from_file(string dir){
	std::ifstream ifs(dir);
	std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );
	return content;
}
void write_text(string dir, string text){
	ofstream outfile (dir);
	outfile << text << endl;
	outfile.close();
	cout << dir << " written" <<endl;
}
