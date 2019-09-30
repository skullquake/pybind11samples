#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//scr
	pybind11::exec(
		R"(
try:
	assert(0==0)
except:
	print("exception")
else:
	print("no exception")
try:
	assert(0==1)
except:
	print("exception")
else:
	print("no exception")
try:
	a=open("./res/a.txt","r")
except IOError:
	print("Could not locate file")
else:
	print(a.read())
try:
	a=open("./Makefile","r")
except IOError:
	print("Could not locate file")
else:
	print(a.read(8)+"...")
try:
	a=open("./res/a.txt","r")
except IOError,a:
	print(a)
else:
	print(a.read())

		)",
		s
	);
	//api
	try{
		pybind11::exec("assert(0==0)",s);
		std::cout<<"not exception"<<std::endl;
	}catch(std::exception e){
		std::cout<<"exception"<<std::endl;
	}
	try{
		pybind11::exec("assert(0==1)",s);
		std::cout<<"not exception"<<std::endl;
	}catch(std::exception e){
		std::cout<<"exception"<<std::endl;
	}
	try{
		pybind11::object fo=pybind11::eval(R"(open("./res/a.txt","r"))",s);
		std::cout<<fo.attr("read")().cast<std::string>()<<std::endl;;
	}catch(std::exception e){
		std::cout<<"Could not locate file"<<std::endl;
	}
	try{
		pybind11::object fo=pybind11::eval(R"(open("./Makefile","r"))",s);
		std::cout<<fo.attr("read")(8).cast<std::string>()<<"..."<<std::endl;;
	}catch(std::exception e){
		std::cout<<"Could not locate file"<<std::endl;
	}
	try{
		pybind11::object fo=pybind11::eval(R"(open("./res/a.txt","r"))",s);
		std::cout<<fo.attr("read")().cast<std::string>()<<std::endl;;
	}catch(std::exception e){
		std::cout<<"Error: "<<e.what()<<std::endl;
	}


	return 0;
}
