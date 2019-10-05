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
print("%s_%s" % ("a","b"))
		)",
		s
	);
	//api
	//std::cout<<pybind11::str(std::string("a_b"))<<std::endl;
	std::cout<<pybind11::str("{a}_{b}").format("a"_a="b","b"_a="b").cast<std::string>()<<std::endl;
	std::cout<<pybind11::str("{}_{}").format("a","b").cast<std::string>()<<std::endl;
	std::cout<<pybind11::str(pybind11::bytes("a",1)).cast<std::string>()<<std::endl;
	return 0;
}

