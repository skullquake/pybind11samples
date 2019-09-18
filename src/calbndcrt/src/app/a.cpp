#include<pybind11/embed.h>
#include<iostream>
#include<fstream>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	if(argc==2){
		std::ifstream t(argv[1]);
		std::string src((std::istreambuf_iterator<char>(t)),std::istreambuf_iterator<char>());
		py::scoped_interpreter guard{};
		py::exec(src);
		return 0;
	}else{
		std::cerr<<"Usage: "<<argv[0]<<" PATH"<<std::endl;
		return -1;
	}

	return 0;
}
