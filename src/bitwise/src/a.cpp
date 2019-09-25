#include<iostream>
#include<pybind11/embed.h>
#include<bitset>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//script
	pybind11::exec(
		R"(
#0011 1100
a=60
print(bin(a))
b=13
print(bin(b))
c=a&b;
print(bin(c))
d=a|b
print(bin(d))
e=a^b
print(bin(e))
f=~a
print(bin(f))
		)",
		scope
	);
	//api
	std::cout<<"--------------------------------------------------------------------------------"<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("a").cast<pybind11::int_>())<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("b").cast<pybind11::int_>())<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("c").cast<pybind11::int_>())<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("d").cast<pybind11::int_>())<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("e").cast<pybind11::int_>())<<std::endl;
	std::cout<<std::bitset<8>(pybind11::eval("f").cast<pybind11::int_>())<<std::endl;
	return 0;
}
