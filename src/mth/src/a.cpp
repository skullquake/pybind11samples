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
	pybind11::exec(
		R"(
import sys
print(sys.path)
import math
#print(abs(x))
#print(ceil(x))
#print(cmp(x,y))
#print(exp(x))
#fabs(x)
#floor(x)
#log(x)
#log10(x)
#max(x1, x2,...)
#min(x1, x2,...)
#modf(x)
#pow(x, y)
#round(x [,n])
#sqrt(x)
		)",
		scope
	);
	//api
	//std::cout<<int(pybind11::eval("x").cast<pybind11::int_>())<<std::endl;
	//scope["x"]=(pybind11::eval("x").cast<pybind11::int_>())+1;
	return 0;
}

