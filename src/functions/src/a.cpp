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
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");

	//script
	pybind11::exec(
		R"(
def add(a,b):
	"adds"
	return a+b
def sub(a,b):
	"adds"
	return a+b
print(add(1,2))
print(sub(1,2))
		)",
		scope
	);
	pybind11::exec(
		R"(
def vadd(*a):
	"vadds"
	b=0
	for c in a:
		b+=c
	return b
def vsub(*a):
	"vadds"
	b=0
	for c in a:
		b-=c
	return b
print(vadd(1,2,3))
print(vsub(1,2,3))
		)",
		scope
	);
	pybind11::exec(
		R"(
ladd=lambda b,c:b+c;
lsub=lambda b,c:b-c;
print(ladd(1,2))
print(lsub(1,2))
print((lambda b,c:b+c)(1,2))
print((lambda b,c:b-c)(1,2))
		)",
		scope
	);

	std::cout<<"----------------------------------------"<<std::endl;
	//api
	auto ebmod=py::module::import("ebmod");
	pybind11::exec(
		R"(
import ebmod 
print(ebmod.add(1,2))
print(ebmod.sub(1,2))
		)",
		scope
	);

	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<ebmod.attr("add")(1, 2).cast<int>()<<std::endl;
	std::cout<<ebmod.attr("sub")(1, 2).cast<int>()<<std::endl;
	return 0;
}
/*
acos(x)
asin(x)
atan(x)
atan2(y, x)
cos(x)
hypot(x, y)
sin(x)
tan(x)
degrees(x)
radians(x)
   */
