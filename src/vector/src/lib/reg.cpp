#include<pybind11/pybind11.h>
#include<pybind11/stl.h>
#include"lib/vmod.h"
#include<string>
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("vmod",&vmod,"Vector passthrough");
}
