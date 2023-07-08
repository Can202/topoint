#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;
int transform_code_to_cpp(string program_location, string output);
void write_text(string dir, string text);
string get_text_from_file(string dir);
vector<string> split(const string &s, char delim);


vector<string> normal_includes = {	"#include <iostream>",
									"#include <fstream>",
									"#include <sstream>",
									"#include <vector>",
									"#include <string>"
									};

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
	
	string text = get_text_from_file(program_location);
	
	vector<string> textsplit = split(text, '\n');
	int size = textsplit.size();
	
	for (int i = 0; i < size; i++){
		cout << textsplit.at(i) << endl;
	}
	
	
	vector<string> thecode;
	
	// includes
	size = normal_includes.size();
	for (int i = 0; i < size; i++){
		thecode.push_back(normal_includes.at(i));
	}
	
	size = thecode.size();
	for (int i = 0; i < size; i++){
		cout << thecode.at(i) << endl;
	}
	
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

std::vector<std::string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
    // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
  }
  return elems;
}
