#include"lib/obj.h"
Obj::Obj(const std::string aP)
	:a(aP)
{
	this->c++;
}
Obj::~Obj()
{
	this->c--;
}
void Obj::setA(const std::string aP){
	this->a=aP;
}
std::string Obj::getA()const{
	return this->a;
}
int Obj::getC(){
	return c;
}
void Obj::setD(const std::string dP){
	this->d=dP;
}
std::string Obj::getD()const{
	return this->d;
}

