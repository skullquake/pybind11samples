#include<iostream>
#include<pybind11/embed.h>
namespace py = pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//auto m=pybind11::module::import("math");
	scope["x"]=-0.5;
	scope["y"]= 0.5;
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import random
random.seed(8)
print(random.random())
print(random.randrange(0,10,2))
print(random.choice([0,1,2,3]))
l=[0,1,2,3]
random.shuffle(l)
print(l)
print(random.uniform(0,1))
		)",
		scope
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::module::import("random").attr("seed")(8);
	std::cout<<pybind11::module::import("random").attr("random")().cast<double>()<<std::endl;
	pybind11::list l;
	l.append(0);
	l.append(1);
	l.append(2);
	l.append(3);
	l.append(4);
	std::cout<<pybind11::module::import("random").attr("choice")(l).cast<int>()<<std::endl;
	std::cout<<pybind11::module::import("random").attr("randrange")(0,10,2).cast<int>()<<std::endl;
	pybind11::module::import("random").attr("shuffle")(l);
	for(auto& a:l){
		std::cout<<(a.cast<int>())<<" ";
	}
	std::cout<<std::endl;
	std::cout<<pybind11::module::import("random").attr("uniform")(0,1).cast<float>()<<std::endl;
	//std::cout<<float(scope.attr["pi"])<<std::endl;//???
	return 0;
}
/*
acos(x)
asin(x)
atan(x)
atan2(y, x)
cos(x)
hypot(x, y)
sin(x)
tan(x)
degrees(x)
radians(x)
   */
