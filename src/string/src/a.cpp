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
	pybind11::str s("foo");
	pybind11::print(s);
	pybind11::print(s,s);
	return 0;
}
