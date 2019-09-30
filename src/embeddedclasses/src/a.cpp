#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
class Obj{
	public:
		Obj(std::string aP="")
			:m_a(aP)
		{
		}
		~Obj(){
		}
		void setA(std::string aP){
			this->m_a=aP;
		}
		std::string getA(){
			return this->m_a;
		}
	private:
		std::string m_a;
};

PYBIND11_EMBEDDED_MODULE(imod,m){
	pybind11::class_<Obj>(m,"Obj")
		.def(pybind11::init<const std::string &>())
		.def("setA",&Obj::setA)
		.def("getA",&Obj::getA)
	;
}
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	auto _Obj=py::module::import("imod");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import imod
o=imod.Obj("a")
print(o)
print(o.getA())
o.setA('b')
print(o.getA())
		)",
		s
	);
	//api
	pybind11::object o=pybind11::module("imod").attr("Obj")("a");
	std::cout<<o.attr("getA")().cast<std::string>()<<std::endl;
	o.attr("setA")("b");
	std::cout<<o.attr("getA")().cast<std::string>()<<std::endl;
	return 0;
}

