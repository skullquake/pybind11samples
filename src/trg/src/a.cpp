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
print(math.acos(x))
print(math.asin(x))
print(math.atan(x))
print(math.atan2(y,x))
print(math.cos(x))
print(math.hypot(x,y))
print(math.sin(x))
print(math.tan(x))
print(math.degrees(x))
print(math.radians(x))
		)",
		scope
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<pybind11::module::import("math").attr("acos")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("asin")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("atan")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("atan2")(1,2).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("cos")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("hypot")(1,2).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("sin")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("tan")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("degrees")(1).cast<float>()<<std::endl;
	std::cout<<pybind11::module::import("math").attr("radians")(1).cast<float>()<<std::endl;
	return 0;
}

