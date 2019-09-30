#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
class Vector{
	public:
		Vector(std::string aP="")
			:m_a(aP)
		{
			std::cout<<"Vector()"<<std::endl;
		}
		~Vector(){
			std::cout<<"~Vector()"<<std::endl;
		}
		//todo:add
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
	pybind11::class_<Vector>(m,"Vector")
		.def(pybind11::init<const std::string &>())
		.def("setA",&Vector::setA)
		.def("getA",&Vector::getA)
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
o=imod.Vector("a")
print(o)
print(o.getA())
o.setA('b')
print(o.getA())
del o
		)",
		s
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::object v=pybind11::module("imod").attr("Vector")("a");
	s["v"]=v;
	std::cout<<v.attr("getA")().cast<std::string>()<<std::endl;
	v.attr("setA")("b");
	std::cout<<v.attr("getA")().cast<std::string>()<<std::endl;
	pybind11::exec("del v",s);//???
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
class Vector:
	def __init__(self,a,b):
		self.a=a
		self.b=b
	def __str__(self):
		return 'Vector (%d, %d)' % (self.a, self.b)
	def __add__(self,other):
		return Vector(self.a + other.a, self.b + other.b)
v1=Vector(2,10)
v2=Vector(5,-2)
print v1+v2
		)",
		s
	);
	std::cout<<"----------------------------------------"<<std::endl;
	return 0;
}

