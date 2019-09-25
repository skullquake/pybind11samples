#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	pybind11::exec("a=0",scope);
	for(int i=0;i<8;i++){
		pybind11::exec("a=a+1",scope);
	}
	int a=pybind11::eval("a",scope).cast<int>();
	std::cout<<a<<std::endl;
	return 0;
}
