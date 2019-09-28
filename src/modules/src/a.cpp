#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
PYBIND11_EMBEDDED_MODULE(ebmod, m) {
	m.def("add",[](int i, int j){
		return i+j;
	});
	m.def("sub",[](int i, int j){
		return i-j;
	});
}
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object main=pybind11::module::import("__main__");
	pybind11::object globals=main.attr("__dict__");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	//api
	pybind11::exec(
		R"(
def add(a,b):
	return a+b
def sub(a,b):
	return a-b
print(add(1,2))
print(sub(1,2))
		)",
		globals
	);
	auto ebmod=py::module::import("ebmod");
	pybind11::exec(
		R"(
import ebmod 
print(ebmod.add(1,2))
print(ebmod.sub(1,2))
print(dir(ebmod))
		)",
		globals
	);

	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<main.attr("add")(1,2).cast<int>()<<std::endl;
	std::cout<<main.attr("sub")(1,2).cast<int>()<<std::endl;
	std::cout<<ebmod.attr("add")(1,2).cast<int>()<<std::endl;
	std::cout<<ebmod.attr("sub")(1,2).cast<int>()<<std::endl;
	//for(auto a:main.attr("dir")(globals["ebmod"])){//???
	//}
	return 0;
}
