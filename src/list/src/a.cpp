#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//script
	pybind11::exec(
		R"(
list = [ 'abcd', 786 , 2.23, 'john', 70.2 ]
tinylist = [123, 'john']
print list          # Prints complete list
print list[0]       # Prints first element of the list
print list[1:3]     # Prints elements starting from 2nd till 3rd
print list[2:]      # Prints elements starting from 3rd element
print tinylist * 2  # Prints list two times
print list + tinylist # Prints concatenated lists
		)",
		scope
	);
	//api
	auto l0=pybind11::eval("list").cast<pybind11::list>();
	for(auto l0e:l0){
		pybind11::print(l0e);
	}
	pybind11::list l;
	l.append("foo");
	l.append("bar");
	l.append("baz");
	l.append("qux");
	l.append("klutz");
	for(int i=0;i<l.size();i++){
		py::print("Entry at position ",i,":",l[i]);
	}
	py::print(l[py::slice(0,-1,l.size())]);
	//api...
	return 0;
}
