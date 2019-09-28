#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
PYBIND11_EMBEDDED_MODULE(ebmod, m) {
	m.def("cin",[](){
		std::string a;
		std::cin>>a;
		return a;
	});
}
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object main=pybind11::module::import("__main__");
	pybind11::object globals=main.attr("__dict__");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
print("input line")
print(raw_input())
		)",
		globals
	);
	//api
	auto ebmod=py::module::import("ebmod");
	pybind11::exec(
		R"(
import ebmod 
print("input line:")
print(ebmod.cin())
		)",
		globals
	);
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<"input line:"<<std::endl;
	std::cout<<ebmod.attr("cin")().cast<std::string>()<<std::endl;
	/*
	std::cout<<main.attr("add")(1,2).cast<int>()<<std::endl;
	std::cout<<main.attr("sub")(1,2).cast<int>()<<std::endl;
	std::cout<<ebmod.attr("add")(1,2).cast<int>()<<std::endl;
	std::cout<<ebmod.attr("sub")(1,2).cast<int>()<<std::endl;
	*/
	return 0;
}
