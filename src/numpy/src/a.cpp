#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import numpy
print(numpy.arange(5,30,2))
		)",
		s
	);
	//api
	for(auto a:pybind11::module::import("numpy").attr("arange")(5,30,2)){
		std::cout<<pybind11::cast<int>(a)<<" ";
	}
	std::cout<<std::endl;
	return 0;
}

