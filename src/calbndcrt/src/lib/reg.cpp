#include<pybind11/pybind11.h>
#include"lib/add.h"
#include"lib/sub.h"
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("add",&add,"A function which adds two numbers");
	m.def("sub",&sub,"A function which subs two numbers");
}
