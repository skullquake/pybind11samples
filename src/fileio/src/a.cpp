#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//scr
	pybind11::exec(
		R"(
import os
fo=open("./res/a","wb")
fo.write("foo\n")
fo.close()
fo=open("./res/a","r+")
print(fo.tell())
print(fo.read())
print(fo.tell())
fo.close()
os.rename("./res/a","./res/a.txt")
fo=open("./res/tmpa.txt","wb")
fo.close()
os.remove("./res/tmpa.txt")
os.mkdir("./res/tmpdira")
print(os.getcwd())
os.chdir("./res/tmpdira")
print(os.getcwd())
os.chdir("../../")
print(os.getcwd())
os.rmdir("./res/tmpdira")
		)",
		s
	);
	//api
	pybind11::object fo=pybind11::eval(R"(open("./res/b","wb"))",s);
	fo.attr("write")("bar\n");
	fo.attr("close")();
	fo=pybind11::eval(R"(open("./res/b","r+"))",s);
	std::cout<<fo.attr("tell")().cast<int>()<<std::endl;;
	std::cout<<fo.attr("read")().cast<std::string>()<<std::endl;;
	std::cout<<fo.attr("tell")().cast<int>()<<std::endl;;
	fo.attr("close")();
	pybind11::module::import("os").attr("rename")("./res/b","./res/b.txt");
	fo=pybind11::eval(R"(open("./res/tmpb.txt","wb"))",s);
	pybind11::module::import("os").attr("remove")("./res/tmpb.txt");
	pybind11::module::import("os").attr("mkdir")("./res/tmpdirb");
	std::cout<<pybind11::module::import("os").attr("getcwd")().cast<std::string>()<<std::endl;;
	pybind11::module::import("os").attr("chdir")("./res/tmpdirb");
	std::cout<<pybind11::module::import("os").attr("getcwd")().cast<std::string>()<<std::endl;;
	pybind11::module::import("os").attr("chdir")("../../");
	std::cout<<pybind11::module::import("os").attr("getcwd")().cast<std::string>()<<std::endl;;
	pybind11::module::import("os").attr("rmdir")("./res/tmpdirb");

	return 0;
}
