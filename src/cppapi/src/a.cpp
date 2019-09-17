#include<pybind11/embed.h>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	py::scoped_interpreter guard{};
	auto kwargs=py::dict("name"_a="World","number"_a=42);
	auto message="Hello,{name}!Theansweris{number}"_s.format(**kwargs);
	py::print(message);
}
