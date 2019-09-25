#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include"lib/add.h"
#include<string>
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("add",pybind11::overload_cast<int,int>(&add),"Add args");
	m.def("add",pybind11::overload_cast<double,double>(&add),"Add args");
}
