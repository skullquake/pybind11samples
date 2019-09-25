#include"lib/vmod.h"
std::vector<double> vmod(const std::vector<double>& a){
	std::vector<double> b;
	for(auto c:a){
		b.push_back(c*2);
	}
	return b;

}
