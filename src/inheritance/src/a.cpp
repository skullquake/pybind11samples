#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
class Obj{
	public:
		Obj(std::string aP="")
			:m_a(aP)
		{
			std::cout<<"Obj()"<<std::endl;
		}
		~Obj(){
			std::cout<<"~Obj()"<<std::endl;
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
class Obj2:public Obj{
	public:
		Obj2(std::string aP="")
			:Obj(aP)
		{
			std::cout<<"Obj2()"<<std::endl;
		}
		~Obj2(){
			std::cout<<"~Obj2()"<<std::endl;
		}
	private:
};


PYBIND11_EMBEDDED_MODULE(imod,m){
	pybind11::class_<Obj>(m,"Obj")
		.def(pybind11::init<const std::string &>())
		.def("setA",&Obj::setA)
		.def("getA",&Obj::getA)
	;
	pybind11::class_<Obj2>(m,"Obj2")
		.def(pybind11::init<const std::string &>())
		.def("setA",&Obj2::setA)
		.def("getA",&Obj2::getA)
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
del o
o2=imod.Obj2("a")
print(o2)
print(o2.getA())
o2.setA('b')
print(o2.getA())
del o2

		)",
		s
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::object o=pybind11::module("imod").attr("Obj")("a");
	s["o"]=o;
	std::cout<<o.attr("getA")().cast<std::string>()<<std::endl;
	o.attr("setA")("b");
	std::cout<<o.attr("getA")().cast<std::string>()<<std::endl;
	pybind11::object o2=pybind11::module("imod").attr("Obj2")("a");
	pybind11::exec("del o",s);//???
	s["o2"]=o2;
	std::cout<<o2.attr("getA")().cast<std::string>()<<std::endl;
	o2.attr("setA")("b");
	std::cout<<o2.attr("getA")().cast<std::string>()<<std::endl;
	pybind11::exec("del o2",s);//???
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
class Parent:
	parentAttr = 100
	def __init__(self):
		print "Calling parent constructor"
	def parentMethod(self):
		print 'Calling parent method'
	def setAttr(self, attr):
		Parent.parentAttr = attr
	def getAttr(self):
		print "Parent attribute :", Parent.parentAttr
	def __del__(self):
		print("Parent destructor")
class Child(Parent): # define child class
	def __init__(self):
		print "Calling child constructor"
	def childMethod(self):
		print 'Calling child method'
	def __del__(self):
		print("Child destructor")
		super(type(self),self).__del__() #???
c=Child()            # instance of child
c.childMethod()      # child calls its method
c.parentMethod()     # calls parent's method
c.setAttr(200)       # again call parent's method
c.getAttr()          # again call parent's method
del c                # some issues here
		)",
		s
	);
	std::cout<<"----------------------------------------"<<std::endl;
	return 0;
}

