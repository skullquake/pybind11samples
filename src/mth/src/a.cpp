#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//auto m=pybind11::module::import("math");
	scope["x"]=-0.5;
	scope["y"]= 0.5;
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import math
print(abs(x))
print(math.ceil(x))
print(cmp(x,y))
print(math.exp(x))
math.fabs(x)
math.floor(x)
#math.log(x)
#math.log10(x)
print(max(x,y))
print(min(x,y))
print(math.modf(x))
print(pow(y,x))
print(round(x,1))
print(math.sqrt(8))
		)",
		scope
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<pybind11::module::import("math").attr("sqrt")(2).cast<double>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("ceil")(2.5).cast<double>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("floor")(2.5).cast<double>()<<std::endl;
	return 0;
}

