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
import re;
a="qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";
b=re.sub( r'qwer','____',a);
print(b);
		)",
		s
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	std::string a="qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";
	pybind11::object b=pybind11::module("re").attr("sub")(R"(qwer)","____",a);
	std::cout<<pybind11::cast<std::string>(b)<<std::endl;
	return 0;
}

