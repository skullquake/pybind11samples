#include<pybind11/embed.h>
#include<iostream>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	py::scoped_interpreter guard{};
	py::exec(R"(
import sys
sys.path.insert(1,'./lib')
sys.path.insert(1,'./lib')
import example
print(example.add(1,2))
)"
	);
	return 0;
}
