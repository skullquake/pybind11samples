#include<iostream>
#include<pybind11/embed.h>
	//cpp
#include<regex>
#include<string>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//script
	pybind11::exec(
		R"(
import re;
import sys;
a=re.compile("^[\-]?[1-9][0-9]*\.?[0-9]+$")
print(' ')
while True:
	sys.stdout.flush()#windowz
	b=raw_input("Enter number [q to quit]: ");
	sys.stdout.flush()#windowsz
	if b.strip()=='q':
		break;
	if re.match(a,b):
		print "is a number"
	else:
		print('is not number')
print('done');
		)",
		s
	);
	//cpp
	std::string input;
	std::regex integer("(\\+|-)?[[:digit:]]+");
	//As long as the input is correct ask for another number
	while(true){
	     std::cout<<"Give me an integer!"<<std::endl;
	     std::cin>>input;
             if(!std::cin) break;
             //Exit when the user inputs q
             if(input=="q")
                     break;
             if(std::regex_match(input,integer))
                     std::cout<<"integer"<<std::endl;
             else
             {
		     std::cout<<"Invalid input"<<std::endl;
             }
	}
	return 0;
}

