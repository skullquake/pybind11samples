#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	pybind11::exec(
		R"(
a=0
)",
		scope
	);
	pybind11::exec(
		R"(
if a==0 :
	print("true")
else :
	print("false")
)",
		scope
	);
	return 0;
}
