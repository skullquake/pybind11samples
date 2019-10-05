#include<iostream>
#include<pybind11/embed.h>
	//cpp
#include<regex>
#include<string>
namespace py=pybind11;
using namespace py::literals;
int main(int argc,char** argv){
	pybind11::scoped_interpreter guard{};
	pybind11::module m=pybind11::module::import("__main__");
	pybind11::object s=m.attr("__dict__");
	//script
	pybind11::exec(
		R"(
import psycopg2
try:
	connection=psycopg2.connect("dbname='test' host='localhost' port=5432");
	print("scon");
	cursor=connection.cursor();
	print(connection.get_dsn_parameters(),"\n");
	cursor.execute("SELECT version();");
	record=cursor.fetchone();
	print("You are connected to - ", record,"\n");
except Exception,e:
	print(e);
finally:
#closing database connection.
	if(connection):
		cursor.close();
		connection.close();
		print("econ");
		)",
		s
	);
	//api
	std::cout<<"----------------------------------------"<<std::endl;
	try{
		pybind11::object connection=pybind11::module("psycopg2").attr("connect")("dbname='test' host='localhost' port=5432");
		std::cout<<"scon";
		pybind11::object cursor=connection.attr("cursor")();
		cursor.attr("execute")("SELECT version();");
		pybind11::object record=cursor.attr("fetchone")();
		pybind11::print(record);
		cursor.attr("execute")(
			R"(
create table if not exists person(
	name varchar(255),
	ssoc varchar(255)
)
			)"
		);
		connection.attr("commit")();
		cursor.attr("execute")(
			pybind11::str(R"(insert into person(name,ssoc)values(%s,%s))"),
			pybind11::make_tuple("foo","bar")
		);
		connection.attr("commit")();
		{
			std::cout<<"----------------------------------------"<<std::endl;
			std::cout<<"cursor.fetchall:"<<std::endl;
			std::cout<<"----------------------------------------"<<std::endl;
			cursor.attr("execute")(
				pybind11::str(R"(select * from person)")
			);
			pybind11::iterable rows=cursor.attr("fetchall")();
			for(auto row:rows){
				std::cout<<row.cast<pybind11::list>()[0].cast<std::string>()<<",";
				std::cout<<row.cast<pybind11::list>()[1].cast<std::string>()<<std::endl;
			}
		}
		{
			std::cout<<"----------------------------------------"<<std::endl;
			std::cout<<"cursor.fetchmany(2):"<<std::endl;
			std::cout<<"----------------------------------------"<<std::endl;
			cursor.attr("execute")(
				pybind11::str(R"(select * from person)")
			);
			//perform fetchmany until result set end
			pybind11::iterable rows;
			do{
				rows=cursor.attr("fetchmany")(8);
				for(auto row:rows){
					std::cout<<row.cast<pybind11::list>()[0].cast<std::string>()<<",";
					std::cout<<row.cast<pybind11::list>()[1].cast<std::string>()<<std::endl;
				}
			}while(cursor.attr("rownumber").cast<int>()<=(cursor.attr("rowcount").cast<int>()-1));
			std::cout<<"----------------------------------------"<<std::endl;
		}
		{
			std::cout<<"----------------------------------------"<<std::endl;
			std::cout<<"cursor.fetchone():"<<std::endl;
			std::cout<<"----------------------------------------"<<std::endl;
			cursor.attr("execute")(pybind11::str(R"(select * from person)"));
			pybind11::iterable row=cursor.attr("fetchone")();
			std::cout<<row.cast<pybind11::list>()[0].cast<std::string>()<<",";
			std::cout<<row.cast<pybind11::list>()[1].cast<std::string>()<<std::endl;
			std::cout<<"----------------------------------------"<<std::endl;
		}
		if(!connection.is_none()){
			cursor.attr("close")();
			connection.attr("close")();
			pybind11::print("econ");
		}
	}catch(std::exception e){
		std::cerr<<e.what()<<std::endl;
	}
	return 0;
}


