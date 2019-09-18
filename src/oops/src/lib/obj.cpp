#include"lib/obj.h"
Obj::Obj(const std::string aP)
	:a(aP)
{
}
void Obj::setA(const std::string aP){
	this->a=aP;
}
std::string Obj::getA()const{
	return this->a;
}
