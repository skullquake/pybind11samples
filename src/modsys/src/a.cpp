#include<pybind11/embed.h>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	py::scoped_interpreter guard{};
	py::module sys = py::module::import("sys");
	py::print(sys.attr("path"));
	return 0;
}
