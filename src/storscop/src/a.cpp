#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	scope["x"]=123;
	//script
	pybind11::exec(
		R"(
print(x)
x=x+1
		)",
		scope
	);
	//api
	std::cout<<int(pybind11::eval("x").cast<pybind11::int_>())<<std::endl;
	scope["x"]=(pybind11::eval("x").cast<pybind11::int_>())+1;
	//script
	pybind11::exec(
		R"(
print(x)
		)",
		scope
	);
	return 0;
}
