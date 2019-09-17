#include<pybind11/embed.h>
namespace py=pybind11;
int main(int argc,char** argv){
	py::scoped_interpreter guard{};
	py::print("Hello, World!");
	return 0;
}
