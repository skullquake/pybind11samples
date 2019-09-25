#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	//script
	pybind11::exec(
			R"(
				a="qwer";
				print(a);
				print(a[0]);
				print(a[0:2]);
				print(a[:2]);
				print(a[2:]);
				print(a*2);
				print(2*a);
				print(a+a);
			  )"
	);
	//api
	pybind11::print("a");
	pybind11::print(1,2,"a");
	pybind11::print(1,2,"a",pybind11::arg("sep")="_");
	auto args=pybind11::make_tuple("unpacked", true);
	pybind11::print("->", *args, pybind11::arg("end")="<-");
	return 0;
}
