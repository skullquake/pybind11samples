#include"lib/enum.h"
#include<iostream>
void getAnimal(int a){
	switch(a){
		case Type::Cat:
			std::cout<<"Cat"<<std::endl;
			break;
		case Type::Dog:
			std::cout<<"Dog"<<std::endl;
			break;
		default:
			std::cerr<<"Unknown type"<<std::endl;
			break;
	}
}
