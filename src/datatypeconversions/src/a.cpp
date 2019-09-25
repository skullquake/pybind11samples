#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//script
	pybind11::exec(
		R"(
a=1.1
b=int(a)
print(a)
print(b)
		)",
		scope
	);
	//api
	int a=pybind11::eval("a").cast<pybind11::float_>();
	float b=pybind11::eval("a").cast<pybind11::int_>();
	std::cout<<a<<std::endl;
	std::cout<<b<<std::endl;
	return 0;
}
