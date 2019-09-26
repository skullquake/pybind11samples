#include<iostream>
#include<pybind11/embed.h>
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::object scope=pybind11::module::import("__main__").attr("__dict__");
	//script
	std::cout<<"----------------------------------------"<<std::endl;
	pybind11::exec(
		R"(
import calendar
cal=calendar.month(2008,1)
print("Here is the calendar:")
print(cal)
		  )"
	);
	std::cout<<"----------------------------------------"<<std::endl;
	std::cout<<pybind11::module::import("calendar").attr("month")(2008,1).cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("calendar").attr("firstweekday")().cast<int>()<<std::endl;
	for(int i=1990;i<2000;i++){
		std::cout<<pybind11::module::import("calendar").attr("isleap")(i).cast<bool>()<<" ";
	}
	std::cout<<std::endl;
	for(int i=1990;i<2000;i++){
		std::cout<<pybind11::module::import("calendar").attr("leapdays")(i,i+1).cast<bool>()<<" ";
	}
	std::cout<<std::endl;
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("iterweekdays")()){
		std::cout<<pybind11::cast<int>(a)<<" ";
	}
	std::cout<<std::endl;
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("itermonthdates")(1990,1)){
		std::cout<<pybind11::cast<std::string>(a.attr("isoformat")())<<" ";
	}
	std::cout<<std::endl;
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("itermonthdays")(1990,1)){
		std::cout<<pybind11::cast<int>(a)<<" ";
	}
	std::cout<<std::endl;
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("itermonthdays2")(1990,1)){
		std::cout<<"["<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(a))[0])<<","<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(a))[1])<<"],";
	}
	std::cout<<std::endl;
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("monthdatescalendar")(1990,1)){
		for(auto b:a){
			std::cout<<pybind11::cast<std::string>(b.attr("isoformat")())<<" ";
		}
		std::cout<<std::endl;
	}
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("monthdays2calendar")(1990,1)){
		for(auto b:a){
			std::cout<<"["<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(b))[0])<<","<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(b))[1])<<"],";
		}
		std::cout<<std::endl;
	}
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("monthdayscalendar")(1990,1)){
		for(auto b:a){
			std::cout<<pybind11::cast<int>(b)<<" ";
		}
		std::cout<<std::endl;
	}
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("yeardatescalendar")(1990)){
		for(auto b:a){
			for(auto c:b){
				for(auto d:c){
					std::cout<<pybind11::cast<std::string>(d.attr("isoformat")())<<" ";
				}
			}
			std::cout<<std::endl;
		}
	}
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("yeardays2calendar")(1990)){
		for(auto b:a){
			for(auto c:b){
				for(auto d:c){
					std::cout<<"["<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(d))[0])<<","<<pybind11::cast<int>((pybind11::cast<pybind11::tuple>(d))[1])<<"],";
				}
			}
			std::cout<<std::endl;
		}
	}
	for(auto a:pybind11::module::import("calendar").attr("Calendar")().attr("yeardayscalendar")(1990)){
		for(auto b:a){
			for(auto c:b){
				for(auto d:c){
					std::cout<<pybind11::cast<int>(d)<<" ";
				}
			}
			std::cout<<std::endl;
		}
	}
	pybind11::module::import("calendar").attr("TextCalendar")().attr("prmonth")(1990,1);
	std::cout<<pybind11::module::import("calendar").attr("TextCalendar")().attr("formatyear")(1990).cast<std::string>()<<std::endl;;
	std::cout<<pybind11::module::import("calendar").attr("HTMLCalendar")().attr("formatmonth")(1990,1).cast<std::string>()<<std::endl;
	std::cout<<pybind11::module::import("calendar").attr("HTMLCalendar")().attr("formatyear")(1990).cast<std::string>()<<std::endl;

	return 0;
}
