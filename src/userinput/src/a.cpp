#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	pybind11::exec(R"(
raw_input("Press the enter key to exit.")
)"
	);
	return 0;
}
