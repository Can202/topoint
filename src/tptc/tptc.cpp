#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>
using namespace std;
int transform_code_to_cpp(string program_location, string output);
void write_text(string dir, string text);
string get_text_from_file(string dir);
vector<string> split(const string &s, char delim);
bool str_in(string s1, string s2);
void get_fuctions(vector<string> textsplit);
string ident(int num);
void read_function(vector<string> textsplit, string function_name);
int when_function_ends(vector<string> textsplit, int function_position);
string rm_prefix(string full_string, string prefix);
string rm_suffix(string full_string, string suffix);
bool str_starts_with(string full_string, string prefix);
vector<string> removeidentation (vector<string> textsplit);
vector<string> remove_after (vector<string> textsplit, string after);
vector<string> withoutstrings (vector<string> textsplit);
void ChangeString(std::string& test);

vector<string> normal_includes = {	"#include <iostream>",
									"#include <fstream>",
									"#include <sstream>",
									"#include <vector>",
									"#include <string>"
									};
int func_start_position = 0;
vector<string> custom_functions;
vector<string> custom_functions_type;
vector<string> custom_functions_arg;
vector<int> custom_functions_position;

vector<string> variable_types = {"int", "float", "number", "string", "bool"};

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
	
	textsplit = removeidentation (textsplit);
	textsplit = remove_after (textsplit, "//");
	
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		cout << textsplit.at(i) << endl;
	}
	
	
	vector<string> thecode;
	
	// includes
	size = normal_includes.size();
	for (int i = 0; i < size; i++){
		thecode.push_back(normal_includes.at(i));
	}
	
	// functions
	get_fuctions(textsplit);
	size = custom_functions.size();
	for (int i = 0; i < size; i++){
		string functext = custom_functions_type.at(i) + " " + custom_functions.at(i) + custom_functions_arg.at(i) + ";";
		thecode.push_back(functext);
	}
	
	// add main function
	thecode.push_back("int main(){");
	read_function(textsplit, "start");
	
	int start_end = when_function_ends(textsplit, func_start_position);
	for (int i = func_start_position; i<=start_end ; i++){
		thecode.push_back(ident(1) + textsplit.at(i));
	}
	
	thecode.push_back(ident(1) + "cosas");
	thecode.push_back("}");
	
	
	// print
	size = thecode.size();
	for (int i = 0; i < size; i++){
		cout << thecode.at(i) << endl;
	}
	
	return 0;
}
int when_function_ends(vector<string> textsplit, int function_position){
	int size = textsplit.size();
	int disparity = 0;
	int end_position = 0;
	bool changed = false;
	for (int i = function_position; i < size; i++){
		if (str_in(textsplit.at(i), " do")){
			changed = true;
			disparity++;
		}
		if (str_in(textsplit.at(i), "exit")){
			changed = true;
			disparity--;
		}
		if (str_in(textsplit.at(i), "else")){
			changed = true;
			disparity--;
		}
		if (disparity == 0 && changed == true){
			end_position = i;
			break;
		}
	}
	return function_position + end_position - 1;
	
}

void read_function(vector<string> textsplit, string function_name){
	int functions_size = custom_functions.size();
	if (function_name == "start"){
		
	} else{
		for (int i = 0; i<functions_size; i++){
			if (function_name == custom_functions.at(i)){
				cout << "good" << function_name << endl;
			}
		}
	}
}

void get_fuctions(vector<string> textsplit){
	int size = textsplit.size();
	for (int i = 0; i < size; i++){
		if (str_in(textsplit.at(i),"func ")){
			if (str_in(textsplit.at(i),"func start")){
				//thecode.push_back("int main(){");
				func_start_position = i;
			} else {
				//thecode.push_back("void");
			}
		} else {
			if (str_in(textsplit.at(i),"func(")){
				int variable_types_size = variable_types.size();
				for (int j = 0; j<variable_types_size; j++){
					if (str_in(textsplit.at(i),"func(" + variable_types.at(j) + ")")){
						vector<string> thisline = split(textsplit.at(i), ' ');
						custom_functions.push_back(thisline[1]);
						custom_functions_type.push_back(variable_types.at(j));
						custom_functions_arg.push_back("()");
						int cfps = custom_functions_position.size();
						custom_functions_position.push_back(cfps);
					}
				}
			}
		}
	}
	
}

bool str_in(string s1, string s2){
	if(strstr(s1.c_str(),s2.c_str()))
	{
	   return true;
	} else{
		return false;
	}
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

vector<string> split(const std::string &s, char delim) {
  std::stringstream ss(s);
  std::string item;
  std::vector<std::string> elems;
  while (std::getline(ss, item, delim)) {
    elems.push_back(item);
    // elems.push_back(std::move(item)); // if C++11 (based on comment from @mchiasson)
  }
  return elems;
}

string ident(int num){
	string nident = "	";
	string tident;
	for (int i = 0; i< num; i++){
		tident = tident + nident;
	}
	return tident;
}

string rm_prefix(string full_string, string prefix){
	string result = full_string.substr(prefix.length());
	return result;
}
string rm_suffix(string full_string, string suffix){
	string result = full_string.substr(0, full_string.length() - suffix.length());
	return result;
}

bool str_starts_with(string full_string, string prefix){
	if (full_string.rfind(prefix, 0) == 0) {
		return true;
	} else {
		return false;
	}
}

vector<string> remove_after (vector<string> textsplit, string after){
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		textsplit.at(i) = textsplit.at(i).substr(0, textsplit.at(i).find(after));
	}
	return textsplit;
}


vector<string> removeidentation (vector<string> textsplit){
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		while (str_starts_with(textsplit.at(i), ident(1) ) ){
			textsplit.at(i) = rm_prefix(textsplit.at(i), ident(1));
		}
	}
	return textsplit;
}

vector<string> withoutstrings (vector<string> textsplit){
	
	return textsplit;
}

void ChangeString(std::string& test)
{
    bool inbracket = false;
    std::string outStr;
    for (size_t i = 0; i < test.size(); ++i)
    { 
        char ch = test[i];
        if (ch == '[') 
           inbracket = true;
        else
        if ( ch == ']')
           inbracket = false;
        else
        if ( !inbracket )
           outStr += ch;
     }
     test = outStr;
}


