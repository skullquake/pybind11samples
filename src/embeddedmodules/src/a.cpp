#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
PYBIND11_EMBEDDED_MODULE(fast_calc, m) {
	m.def("add", [](int i, int j) {
		return i + j;
	});
}
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	auto fast_calc = py::module::import("fast_calc");
	scope["x"]=-0.5;
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import fast_calc
print(fast_calc.add(1,2))
		)",
		scope
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<fast_calc.attr("add")(1, 2).cast<int>()<<std::endl;
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
