#include<pybind11/pybind11.h>
#include"lib/add.h"
#include"lib/sub.h"
#include"lib/obj.h"
#include<string>
PYBIND11_MODULE(example,m){
	m.doc()="pybind11 example plugin";
	m.def("add",&add,"A function which adds two numbers",pybind11::arg("i")=1,pybind11::arg("j")=2);
	m.def("sub",&sub,"A function which subs two numbers",pybind11::arg("i")=1,pybind11::arg("j")=2);
	pybind11::class_<Obj>(m,"Obj",pybind11::dynamic_attr())
		.def(pybind11::init<const std::string &>())
		.def("setA",&Obj::setA)
		.def_property("a",&Obj::getA,&Obj::setA)
		.def("getA",&Obj::getA)
		.def_readwrite("b",&Obj::b)
		.def_static("getC",&Obj::getC)
		.def("setD",&Obj::setD)
		.def("getD",&Obj::getD)
		.def_readonly("d",&Obj::d)
		.def(
			"__repr__",
			[](const Obj &a){
				return "<example.Obj["+a.getA()+","+a.b+"]>";
			}
		)
	;
}
