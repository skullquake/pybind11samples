#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include"lib/enum.h"
#include<string>
PYBIND11_MODULE(example,m){
	pybind11::module sm=m.def_submodule("Type","Type enumerator");
	pybind11::enum_<Type::Value>(sm,"Type")
		.value("Cat",Type::Cat)
		.value("Dog",Type::Dog)
		.export_values()
	;
	m.def("getAnimal",&getAnimal,"Enum test");
}
