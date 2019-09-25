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
			tuple = ( 'abcd', 786 , 2.23, 'john', 70.2  )
			tinytuple = (123, 'john')
			print tuple           # Prints complete list
			print tuple[0]        # Prints first element of the list
			print tuple[1:3]      # Prints elements starting from 2nd till 3rd
			print tuple[2:]       # Prints elements starting from 3rd element
			print tinytuple * 2   # Prints list two times
			print tuple + tinytuple # Prints concatenated lists
		)",
		scope
	);
	auto t0=py::eval("tuple").cast<py::tuple>();
	for(auto t0e:t0){
		py::print(t0e);
	}
	//api
	auto t=py::make_tuple("and","a","custom","separator");
	for(int i=0;i<t.size();i++){
		py::print("Entry at position ",i,":",t[i]);
	}
	py::print(t[py::slice(0,-1,t.size())]);


	return 0;
}
