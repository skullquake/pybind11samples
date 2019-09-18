#ifndef LIB_OBJ_H
#define LIB_OBJ_H
#include<string>
class Obj{
	public:
		Obj(const std::string);
		void setA(const std::string);
		std::string getA()const;
	private:
		std::string a;
};
#endif
