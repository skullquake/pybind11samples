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
	std::cout<<"----------------------------------------"<<std::endl;
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
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::object a=pybind11::module("re").attr("compile")(R"(^[\-]?[1-9][0-9]*\.?[0-9]+$")");
	while(true){
		pybind11::object b=eval(R"(raw_input("Enter number [q to quit]: "))",s);
		if(b.attr("strip")().cast<std::string>().compare("q")==0)
			break;
		if(pybind11::module("re").attr("match")(a,b).cast<bool>())//???
			std::cout<<"is a number"<<std::endl;
		else
			std::cout<<"is not a number"<<std::endl;
	}
	return 0;
}

