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
kwargs = dict(name="World", number=42)
message = "Hello, {name}! The answer is {number}".format(**kwargs)
print(message)
		)",
		scope
	);
	//api
	auto d0=pybind11::eval("kwargs",scope).cast<pybind11::dict>();
	for(auto d0e:d0)
		pybind11::print("key:{},value={}"_s.format(d0e.first,d0e.second));
	auto kwargs=py::dict("name"_a="World","number"_a=42);
	auto message="Hello, {name}! The answer is {number}"_s.format(**kwargs);
	py::print(message);
	for(auto de:kwargs)
		pybind11::print("key:{},value={}"_s.format(de.first,de.second));
	return 0;
}
