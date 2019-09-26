#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import time
print(time.time())
print(time.localtime(time.time()))
print(time.asctime(time.localtime(time.time())))
print(time.altzone)
print(time.clock())
		  )"
	);
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<pybind11::module::import("time").attr("time")().cast<double>()<<std::endl;
	for(auto a:pybind11::eval("time.localtime(time.time())")){
		std::cout<<pybind11::cast<float>(a)<<std::endl;
	}
	std::cout<<pybind11::eval("time.asctime(time.localtime(time.time()))").cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("time").attr("altzone").cast<float>()<<std::endl;
	scope["t"]=pybind11::module::import("time").attr("mktime")(pybind11::make_tuple(1990,1,1,1,1,1,1,1,1));
	std::cout<<pybind11::eval("time.asctime(time.localtime(t))").cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("time").attr("asctime")(pybind11::module::import("time").attr("localtime")(scope["t"])).cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("time").attr("asctime")(pybind11::module::import("time").attr("gmtime")(0)).cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("time").attr("asctime")(pybind11::module::import("time").attr("localtime")(0)).cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("time").attr("asctime")(pybind11::module::import("time").attr("strptime")("1 Jan 90","%d %b %y")).cast<std::string>()<<std::endl;
	pybind11::module::import("time").attr("sleep")(1);
	return 0;
}
