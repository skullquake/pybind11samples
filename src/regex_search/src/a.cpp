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
b=re.match( r'qwer',a,re.M|re.I);
if b:
	print(b.group());
else:
	print("none");
c=re.search( r'rewq',a,re.M|re.I);
if c:
	print(c.group());
else:
	print("none");
		)",
		s
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	std::string a="qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm";
	pybind11::object b=pybind11::module("re").attr("match")(R"(qwer)",a,pybind11::module("re").attr("M")|pybind11::module("re").attr("I"));
	if(!b.is_none()){
		std::cout<<b.attr("group")().cast<std::string>()<<std::endl;
	}else{
		std::cout<<"none"<<std::endl;
	}
	pybind11::object c=pybind11::module("re").attr("match")(R"(rewq)",a,pybind11::module("re").attr("M")|pybind11::module("re").attr("I"));
	if(!c.is_none()){
		std::cout<<c.attr("group")().cast<std::string>()<<std::endl;
	}else{
		std::cout<<"none"<<std::endl;
	}
	return 0;
}

