#include<pybind11/embed.h>
#include<iostream>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	py::scoped_interpreter guard{};
	py::module calc=py::module::import("calc");
	py::object result=calc.attr("add")(1,2);
	int n=result.cast<int>();
	std::cout<<n<<std::endl;
	assert(n==3);
	return 0;
}
