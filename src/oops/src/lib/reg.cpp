#include<pybind11/pybind11.h>
#include"lib/add.h"
#include"lib/sub.h"
#include"lib/obj.h"
#include<string>
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("add",&add,"A function which adds two numbers",pybind11::arg("i")=1,pybind11::arg("j")=2);
	m.def("sub",&sub,"A function which subs two numbers",pybind11::arg("i")=1,pybind11::arg("j")=2);
	pybind11::class_<Obj>(m,"Obj")
		.def(pybind11::init<const std::string &>())
		//.def("setA",&Obj::setA,pybind11::arg("i")="")
		.def("setA",&Obj::setA)
		.def("getA",&Obj::getA)
	;
}
