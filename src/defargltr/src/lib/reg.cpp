#include<pybind11/pybind11.h>
#include"lib/add.h"
#include"lib/sub.h"
using namespace pybind11::literals;
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("add",&add,"A function which adds two numbers","i"_a=1,"j"_a=2);
	m.def("sub",&sub,"A function which subs two numbers","i"_a=1,"j"_a=2);
}
