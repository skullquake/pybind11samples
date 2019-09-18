#ifndef LIB_OBJ_H
#define LIB_OBJ_H
#include<string>
class Obj{
	public:
		Obj(const std::string);
		~Obj();
		void setA(const std::string);
		std::string getA()const;
		static int getC();
		void setD(const std::string);
		std::string getD()const;
		std::string b;
		std::string d;
	private:
		std::string a;
		inline static int c;
};
#endif
