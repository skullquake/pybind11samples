#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//scr
	pybind11::exec(
		R"(
try:
	assert(0==0)
except:
	print("exception")
else:
	print("no exception")
try:
	assert(0==1)
except:
	print("exception")
else:
	print("no exception")
		)",
		s
	);
	//api
	try{
		pybind11::exec("assert(0==0)",s);
		std::cout<<"not exception"<<std::endl;
	}catch(std::exception e){
		std::cout<<"exception"<<std::endl;
	}
	try{
		pybind11::exec("assert(0==1)",s);
		std::cout<<"not exception"<<std::endl;
	}catch(std::exception e){
		std::cout<<"exception"<<std::endl;
	}
	return 0;
}
