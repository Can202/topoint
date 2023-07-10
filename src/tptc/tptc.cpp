#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstring>

#include "string_functions.h"

using namespace std;

int transform_code_to_cpp(string program_location, string output);
void write_text(string dir, string text);
string get_text_from_file(string dir);
vector<string> split(const string &s, char delim);
void get_fuctions(vector<string> textsplit);
void read_function(vector<string> textsplit, string function_name);
int when_function_ends(vector<string> textsplit, int function_position);
string transform_line_to_cpp(string line);
int get_actual_identation (vector<string> textsplit, int position);


bool compile = true;

vector<string> normal_includes = {	"#include <iostream>",
									"#include <fstream>",
									"#include <sstream>",
									"#include <vector>",
									"#include <string>",
									"using namespace std;"
									};
int func_start_position = 0;
vector<string> custom_functions;
vector<string> custom_functions_type;
vector<string> custom_functions_arg;
vector<int> custom_functions_position;
vector<string> variable_types = {"int", "float", "number", "string", "bool"};
int actual_identation = 0;

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
	
	vector<string> textsplitwostr = withoutstrings(textsplit);
	
	int size = textsplit.size();
	for (int i = 0; i<size; i++){
		cout << textsplitwostr.at(i) << endl;
	}
	
	
	vector<string> thecode;
	
	// includes
	size = normal_includes.size();
	for (int i = 0; i < size; i++){
		thecode.push_back(normal_includes.at(i));
	}
	
	// functions
	get_fuctions(textsplitwostr);
	size = custom_functions.size();
	for (int i = 0; i < size; i++){
		string functext = custom_functions_type.at(i) + " " + custom_functions.at(i) + custom_functions_arg.at(i) + ";";
		thecode.push_back(functext);
	}
	
	// add main function
	thecode.push_back("int main(){");
	read_function(textsplitwostr, "start");
	
	int start_end = when_function_ends(textsplitwostr, func_start_position);
	for (int i = func_start_position + 1; i<=start_end -1 ; i++){
		actual_identation = get_actual_identation(textsplit, i);
		string line = transform_line_to_cpp(textsplit.at(i));
		thecode.push_back(line);
	}
	thecode.push_back("}");
	
	
	// print
	size = thecode.size();
	string thecodeinonestring;
	for (int i = 0; i < size; i++){
		if (compile){
			thecodeinonestring = thecodeinonestring + thecode.at(i) + "\n";
		} else {
			cout << thecode.at(i) << endl;
		}
	}
	if (compile){
		write_text("text.cpp",thecodeinonestring);
		system("g++ text.cpp");
		system("rm text.cpp");
	}
	
	return 0;
}

int get_actual_identation (vector<string> textsplit, int position){
	int disparity = 0;
	int size = textsplit.size();
	int more_next = 0;
	for (int i = 0; i < size; i++){
		if (more_next == 1){
			disparity++;
			more_next = 0;
		}
		
		if (str_in(textsplit.at(i), " do")){
			more_next = 1;
		}
		if (str_in(textsplit.at(i), "exit")){
			more_next = 1;
			disparity--;
		}
		if (str_in(textsplit.at(i), "else")){
			more_next = 1;
			disparity--;
		}
		if (i >= position){
			break;
		}
	}
	return disparity;
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







string transform_line_to_cpp(string original_line){
	string original_line_noid = ChangeString(original_line, '"', '"');
	string new_line;
	bool used = false;
	
	string line = ident(actual_identation);
	int size = variable_types.size();
	for (int i = 0; i < size; i++){
		if (str_starts_with(original_line, variable_types.at(i) ) ){
			new_line = original_line + ";";
			used = true;
		}
	}
	
	if (str_starts_with(original_line, "print")){
		string in_str = get_inside_str(original_line, '(', ')');
		vector<string> in_str_split = split(in_str, ',');
		string the_end = "\"\\n\"";
		string stt = "";
		new_line = "std::cout";
		for (size_t i = 0; i < in_str_split.size(); i++){
			cout << in_str_split.at(i) << endl;
			if ( str_in(ChangeString(in_str_split.at(i), '"', '"'), "end") ){
				the_end = "\"" + get_inside_str( in_str_split.at(i), '"', '"') + "\"";
			} else {
				stt = in_str_split.at(i);
				new_line = new_line + " << " + stt;
			}
		}
		new_line = new_line + " << " + the_end + ";";
		used = true;
	}
	if (str_starts_with(original_line, "ask")){
		string in_str = get_inside_str(original_line, '(', ')');
		vector<string> in_str_split = split(in_str, ',');
		string the_end = "\"\\n\"";
		string stt = "";
		new_line = "std::cin";
		for (size_t i = 0; i < in_str_split.size(); i++){
			if (i==0){
				new_line = new_line + " >> " + in_str_split.at(i) + ";";
			} else if (i==1){
				if ( str_in(ChangeString(in_str_split.at(i), '"', '"'), "if_not") ){
					the_end = get_inside_str( in_str_split.at(i), '"', '"');
					// while (true){if(!cin){cout << "Bad value!";cin.clear();cin.ignore();cin >> a;} else{break;}}
					new_line = 	new_line + "while (true){if(!std::cin){std::cout << \"" +
								the_end + "\";std::cin.clear();std::cin.ignore();std::cin >> " +
								in_str_split.at(0) + ";} else{break;}}";
				}
			}
		}
		used = true;
	}
	if (str_starts_with(original_line, "if")){
		vector<string> the_split = split(original_line_noid, ' ');
		int the_split_size = the_split.size();
		new_line = "";
		for (int i=0; i<the_split_size; i++){
			if (str_in(the_split.at(i), "if")){
				new_line += "if (";
			}
			else if (str_in(the_split.at(i), "is")){
				new_line += "==";
			}
			else if (str_in(the_split.at(i), "do")){
				new_line += "){";
			}
			else{
				new_line += the_split.at(i);
			}
			
		}
		used = true;
	}
	if (str_starts_with(original_line, "exit")){
		new_line = "}";
		used = true;
	}
	if (str_starts_with(original_line, "else")){
		bool was_if = false;
		vector<string> the_split = split(original_line_noid, ' ');
		int the_split_size = the_split.size();
		new_line = "";
		for (int i=0; i<the_split_size; i++){
			if (str_in(the_split.at(i), "if")){
				new_line += "if (";
				was_if = true;
			}
			else if (str_in(the_split.at(i), "is")){
				new_line += "==";
			}
			else if (str_in(the_split.at(i), "do")){
				if (was_if){
					new_line += "){";
				} else{
					new_line += "{";
				}
			}
			else if (str_in(the_split.at(i), "else")){
				new_line += "} else";
			}
			else{
				new_line += the_split.at(i);
			}
			
		}
		used = true;
	}
	
	
	if (used == false){
		new_line = original_line;
	}
	
	line = line + new_line;
	return line;
}
